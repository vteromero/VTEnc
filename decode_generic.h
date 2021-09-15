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

#define DecodeCtx(_width_) PASTE2(DecodeCtx, _width_)
#define decctx_init(_width_) WIDTH_SUFFIX(decctx_init, _width_)
#define decode_lower_bits_step(_width_) WIDTH_SUFFIX(decode_lower_bits_step, _width_)
#define decode_lower_bits(_width_) WIDTH_SUFFIX(decode_lower_bits, _width_)
#define decode_full_subtree(_width_) WIDTH_SUFFIX(decode_full_subtree, _width_)
#define set_ones_at_bit_pos(_width_) WIDTH_SUFFIX(set_ones_at_bit_pos, _width_)
#define bcltree_add(_width_) WIDTH_SUFFIX(bcltree_add, _width_)
#define bcltree_visit(_width_) WIDTH_SUFFIX(bcltree_visit, _width_)
#define bcltree_has_more(_width_) WIDTH_SUFFIX(bcltree_has_more, _width_)
#define bcltree_next(_width_) WIDTH_SUFFIX(bcltree_next, _width_)
#define decode_bit_cluster_tree(_width_) WIDTH_SUFFIX(decode_bit_cluster_tree, _width_)
#define vtenc_decode(_width_) WIDTH_SUFFIX(vtenc_decode, _width_)

#define DEC_RETURN_WITH_CODE(dec, code) \
do {                                    \
  (dec)->last_error_code = code;        \
  return;                               \
} while (0)

#define DEC_RETURN_ON_ERROR(dec, exp)   \
do {                                    \
  const VtencErrorCode code = (exp);    \
  if (code != VtencErrorNoError) {      \
    DEC_RETURN_WITH_CODE(dec, code);    \
  }                                     \
} while (0)

struct DecodeCtx(WIDTH) {
  TYPE                    *values;
  size_t                  values_len;
  int                     reconstruct_full_subtrees;
  size_t                  min_cluster_length;
  struct decode_stack     stack;
  struct BSReader         bits_reader;
};

static VtencErrorCode decctx_init(WIDTH)(struct DecodeCtx(WIDTH) *ctx,
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

  decode_stack_init(&ctx->stack);

  bsreader_init(&(ctx->bits_reader), in, in_len);

  return VtencErrorNoError;
}

static inline VtencErrorCode decode_lower_bits_step(WIDTH)(struct DecodeCtx(WIDTH) *ctx,
  TYPE *value, unsigned int n_bits)
{
#if WIDTH > BIT_STREAM_MAX_READ
  uint64_t lower;
  unsigned int shift = 0;

  if (n_bits > BIT_STREAM_MAX_READ) {
    RETURN_IF_ERROR(bsreader_read(&(ctx->bits_reader), BIT_STREAM_MAX_READ, &lower));
    *value |= lower;
    shift = BIT_STREAM_MAX_READ;
    n_bits -= BIT_STREAM_MAX_READ;
  }

  RETURN_IF_ERROR(bsreader_read(&(ctx->bits_reader), n_bits, &lower));
  *value |= lower << shift;

  return VtencErrorNoError;
#else
  uint64_t lower;

  RETURN_IF_ERROR(bsreader_read(&(ctx->bits_reader), n_bits, &lower));
  *value |= (TYPE)lower;

  return VtencErrorNoError;
#endif
}

static inline VtencErrorCode decode_lower_bits(WIDTH)(struct DecodeCtx(WIDTH) *ctx,
  TYPE *values, size_t values_len, unsigned int n_bits)
{
  size_t i;

  for (i = 0; i < values_len; ++i) {
    RETURN_IF_ERROR(decode_lower_bits_step(WIDTH)(ctx, &values[i], n_bits));
  }

  return VtencErrorNoError;
}

static inline void decode_full_subtree(WIDTH)(TYPE *values, size_t values_len)
{
  size_t i;

  for (i = 0; i < values_len; ++i) {
    values[i] |= (TYPE)i;
  }
}

static inline void set_ones_at_bit_pos(WIDTH)(TYPE *values,
  size_t values_len, unsigned int bit_pos)
{
  const TYPE mask = (TYPE)1 << bit_pos;
  size_t i;

  for (i = 0; i < values_len; ++i) {
    values[i] |= mask;
  }
}

static inline void bcltree_add(WIDTH)(struct DecodeCtx(WIDTH) *ctx,
  size_t cl_from, size_t cl_len, unsigned int cl_bit_pos)
{
  if (cl_bit_pos == 0)
    return;

  if (cl_len == 0)
    return;

  decode_stack_push(&ctx->stack, &(struct BitCluster){cl_from, cl_len, cl_bit_pos});
}

static inline int bcltree_has_more(WIDTH)(struct DecodeCtx(WIDTH) *ctx)
{
  return !decode_stack_empty(&ctx->stack);
}

static inline struct BitCluster *bcltree_next(WIDTH)(struct DecodeCtx(WIDTH) *ctx)
{
  return decode_stack_pop(&ctx->stack);
}

static VtencErrorCode decode_bit_cluster_tree(WIDTH)(struct DecodeCtx(WIDTH) *ctx)
{
  bcltree_add(WIDTH)(ctx, 0, ctx->values_len, WIDTH);

  while (bcltree_has_more(WIDTH)(ctx)) {
    struct BitCluster *cluster = bcltree_next(WIDTH)(ctx);
    size_t cl_from = cluster->from;
    size_t cl_len = cluster->length;
    unsigned int cl_bit_pos = cluster->bit_pos;
    unsigned int cur_bit_pos = cl_bit_pos - 1;
    unsigned int enc_len;
    uint64_t n_zeros;

    if (ctx->reconstruct_full_subtrees && is_full_subtree(cl_len, cl_bit_pos)) {
      decode_full_subtree(WIDTH)(ctx->values + cl_from, cl_len);
      continue;
    }

    if (cl_len <= ctx->min_cluster_length) {
      RETURN_IF_ERROR(decode_lower_bits(WIDTH)(ctx, ctx->values + cl_from, cl_len, cl_bit_pos));
      continue;
    }

    enc_len = bits_len_u64(cl_len);
    RETURN_IF_ERROR(bsreader_read(&(ctx->bits_reader), enc_len, &n_zeros));

    if (n_zeros > (uint64_t)cl_len) return VtencErrorWrongFormat;

    set_ones_at_bit_pos(WIDTH)(ctx->values + cl_from + n_zeros, cl_len - n_zeros, cur_bit_pos);

    bcltree_add(WIDTH)(ctx, cl_from + n_zeros, cl_len - n_zeros, cur_bit_pos);
    bcltree_add(WIDTH)(ctx, cl_from, n_zeros, cur_bit_pos);
  }

  return VtencErrorNoError;
}

void vtenc_decode(WIDTH)(VtencDecoder *dec, const uint8_t *in, size_t in_len,
  TYPE *out, size_t out_len)
{
  struct DecodeCtx(WIDTH) ctx;
  uint64_t max_values = dec->allow_repeated_values ? LIST_MAX_VALUES : SET_MAX_VALUES;

  dec->last_error_code = VtencErrorNoError;

  DEC_RETURN_ON_ERROR(dec,
    decctx_init(WIDTH)(&ctx, dec, in, in_len, out, out_len)
  );

  if ((uint64_t)out_len > max_values) {
    DEC_RETURN_WITH_CODE(dec, VtencErrorOutputTooBig);
  }

  memset(out, 0, out_len * sizeof(*out));

  DEC_RETURN_ON_ERROR(dec, decode_bit_cluster_tree(WIDTH)(&ctx));
}
