/**
  Copyright (c) 2019 Vicente Romero Calero. All rights reserved.
  Licensed under the MIT License.
  See LICENSE file in the project root for full license information.
 */
#include <assert.h>
#include <stddef.h>
#include <stdint.h>

#include "bitstream.h"
#include "common.h"
#include "error.h"
#include "internals.h"

#define decctx_(_width_) BITWIDTH_SUFFIX(decctx, _width_)
#define decctx decctx_(BITWIDTH)
#define decctx_init_(_width_) BITWIDTH_SUFFIX(decctx_init, _width_)
#define decctx_init decctx_init_(BITWIDTH)
#define decode_lower_bits_step_(_width_) BITWIDTH_SUFFIX(decode_lower_bits_step, _width_)
#define decode_lower_bits_step decode_lower_bits_step_(BITWIDTH)
#define decode_lower_bits_(_width_) BITWIDTH_SUFFIX(decode_lower_bits, _width_)
#define decode_lower_bits decode_lower_bits_(BITWIDTH)
#define decode_full_subtree_(_width_) BITWIDTH_SUFFIX(decode_full_subtree, _width_)
#define decode_full_subtree decode_full_subtree_(BITWIDTH)
#define bcltree_add_(_width_) BITWIDTH_SUFFIX(bcltree_add, _width_)
#define bcltree_add bcltree_add_(BITWIDTH)
#define bcltree_has_more_(_width_) BITWIDTH_SUFFIX(bcltree_has_more, _width_)
#define bcltree_has_more bcltree_has_more_(BITWIDTH)
#define bcltree_next_(_width_) BITWIDTH_SUFFIX(bcltree_next, _width_)
#define bcltree_next bcltree_next_(BITWIDTH)
#define decode_bit_cluster_tree_(_width_) BITWIDTH_SUFFIX(decode_bit_cluster_tree, _width_)
#define decode_bit_cluster_tree decode_bit_cluster_tree_(BITWIDTH)
#define vtenc_decode_(_width_) BITWIDTH_SUFFIX(vtenc_decode, _width_)
#define vtenc_decode vtenc_decode_(BITWIDTH)

#define dec_return_with_code(dec, code) \
do {                                    \
  (dec)->last_error_code = code;        \
  return;                               \
} while (0)

#define dec_return_on_error(dec, exp)   \
do {                                    \
  const VtencErrorCode code = (exp);    \
  if (code != VtencErrorNoError) {      \
    dec_return_with_code(dec, code);    \
  }                                     \
} while (0)

struct decctx {
  TYPE              *values;
  size_t            values_len;
  int               reconstruct_full_subtrees;
  size_t            min_cluster_length;
  struct dec_stack  stack;
  struct bsreader   bits_reader;
};

static VtencErrorCode decctx_init(struct decctx *ctx,
  const VtencDecoder *dec, const uint8_t *in, size_t in_len,
  TYPE *out, size_t out_len)
{
  ctx->values = out;
  ctx->values_len = out_len;

  /**
   * `skip_full_subtrees` parameter is only applicable to sets, i.e. sequences
   * with no repeated values.
   */
  ctx->reconstruct_full_subtrees = !dec->allow_repeated_values && dec->skip_full_subtrees;

  ctx->min_cluster_length = dec->min_cluster_length;

  dec_stack_init(&ctx->stack);

  bsreader_init(&(ctx->bits_reader), in, in_len);

  return VtencErrorNoError;
}

static inline VtencErrorCode decode_lower_bits_step(struct decctx *ctx,
  TYPE *value, unsigned int n_bits)
{
#if BITWIDTH > BIT_STREAM_MAX_READ
  uint64_t lower;
  unsigned int shift = 0;

  if (n_bits > BIT_STREAM_MAX_READ) {
    return_if_error(bsreader_read(&(ctx->bits_reader), BIT_STREAM_MAX_READ, &lower));
    *value |= lower;
    shift = BIT_STREAM_MAX_READ;
    n_bits -= BIT_STREAM_MAX_READ;
  }

  return_if_error(bsreader_read(&(ctx->bits_reader), n_bits, &lower));
  *value |= lower << shift;

  return VtencErrorNoError;
#else
  uint64_t lower;

  return_if_error(bsreader_read(&(ctx->bits_reader), n_bits, &lower));
  *value |= (TYPE)lower;

  return VtencErrorNoError;
#endif
}

static inline VtencErrorCode decode_lower_bits(struct decctx *ctx,
  TYPE *values, size_t values_len, unsigned int n_bits, TYPE higher_bits)
{
  size_t i;

  for (i = 0; i < values_len; ++i) {
    values[i] = higher_bits;
    return_if_error(decode_lower_bits_step(ctx, &values[i], n_bits));
  }

  return VtencErrorNoError;
}

static inline void decode_full_subtree(TYPE *values, size_t values_len, TYPE higher_bits)
{
  size_t i;

  for (i = 0; i < values_len; ++i) {
    values[i] = higher_bits | (TYPE)i;
  }
}

static inline void bcltree_add(struct decctx *ctx,
  const struct dec_bit_cluster *cluster)
{
  if (cluster->length == 0)
    return;

  dec_stack_push(&ctx->stack, cluster);
}

static inline int bcltree_has_more(struct decctx *ctx)
{
  return !dec_stack_empty(&ctx->stack);
}

static inline struct dec_bit_cluster *bcltree_next(struct decctx *ctx)
{
  return dec_stack_pop(&ctx->stack);
}

static VtencErrorCode decode_bit_cluster_tree(struct decctx *ctx)
{
  bcltree_add(ctx, &(struct dec_bit_cluster){0, ctx->values_len, BITWIDTH, 0});

  while (bcltree_has_more(ctx)) {
    struct dec_bit_cluster *cluster = bcltree_next(ctx);
    size_t cl_from = cluster->from;
    size_t cl_len = cluster->length;
    unsigned int cl_bit_pos = cluster->bit_pos;
    uint64_t cl_higher_bits = cluster->higher_bits;
    uint64_t n_zeros;
    unsigned int enc_len;

    if (cl_bit_pos == 0) {
      size_t i;

      for (i = 0; i < cl_len; i++) {
        ctx->values[cl_from + i] = (TYPE)cl_higher_bits;
      }

      continue;
    }

    if (ctx->reconstruct_full_subtrees && is_full_subtree(cl_len, cl_bit_pos)) {
      decode_full_subtree(ctx->values + cl_from, cl_len, cl_higher_bits);
      continue;
    }

    if (cl_len <= ctx->min_cluster_length) {
      return_if_error(decode_lower_bits(ctx, ctx->values + cl_from, cl_len, cl_bit_pos, cl_higher_bits));
      continue;
    }

    enc_len = bits_len_u64(cl_len);

    return_if_error(bsreader_read(&(ctx->bits_reader), enc_len, &n_zeros));

    if (n_zeros > (uint64_t)cl_len) return VtencErrorWrongFormat;

    {
      unsigned int next_bit_pos = cl_bit_pos - 1;
      struct dec_bit_cluster zeros_cluster = {cl_from, n_zeros, next_bit_pos, cl_higher_bits};
      struct dec_bit_cluster ones_cluster = {cl_from + n_zeros, cl_len - n_zeros, next_bit_pos, cl_higher_bits | (1LL << (next_bit_pos))};

      bcltree_add(ctx, &ones_cluster);
      bcltree_add(ctx, &zeros_cluster);
    }
  }

  return VtencErrorNoError;
}

void vtenc_decode(VtencDecoder *dec, const uint8_t *in, size_t in_len,
  TYPE *out, size_t out_len)
{
  struct decctx ctx;
  uint64_t max_values = dec->allow_repeated_values ? LIST_MAX_VALUES : SET_MAX_VALUES;

  dec->last_error_code = VtencErrorNoError;

  dec_return_on_error(dec,
    decctx_init(&ctx, dec, in, in_len, out, out_len)
  );

  if ((uint64_t)out_len > max_values) {
    dec_return_with_code(dec, VtencErrorOutputTooBig);
  }

  memset(out, 0, out_len * sizeof(*out));

  dec_return_on_error(dec, decode_bit_cluster_tree(&ctx));
}
