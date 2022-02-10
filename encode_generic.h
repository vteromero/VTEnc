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
#include "countbits.h"
#include "error.h"
#include "internals.h"

#define encctx_(_width_) BITWIDTH_SUFFIX(encctx, _width_)
#define encctx encctx_(BITWIDTH)
#define encctx_init_(_width_) BITWIDTH_SUFFIX(encctx_init, _width_)
#define encctx_init encctx_init_(BITWIDTH)
#define encctx_close_(_width_) BITWIDTH_SUFFIX(encctx_close, _width_)
#define encctx_close encctx_close_(BITWIDTH)
#define count_zeros_at_bit_pos_(_width_) BITWIDTH_SUFFIX(count_zeros_at_bit_pos, _width_)
#define count_zeros_at_bit_pos count_zeros_at_bit_pos_(BITWIDTH)
#define encode_lower_bits_step_(_width_) BITWIDTH_SUFFIX(encode_lower_bits_step, _width_)
#define encode_lower_bits_step encode_lower_bits_step_(BITWIDTH)
#define encode_lower_bits_(_width_) BITWIDTH_SUFFIX(encode_lower_bits, _width_)
#define encode_lower_bits encode_lower_bits_(BITWIDTH)
#define bcltree_add_(_width_) BITWIDTH_SUFFIX(bcltree_add, _width_)
#define bcltree_add bcltree_add_(BITWIDTH)
#define bcltree_has_more_(_width_) BITWIDTH_SUFFIX(bcltree_has_more, _width_)
#define bcltree_has_more bcltree_has_more_(BITWIDTH)
#define bcltree_next_(_width_) BITWIDTH_SUFFIX(bcltree_next, _width_)
#define bcltree_next bcltree_next_(BITWIDTH)
#define encode_bit_cluster_tree_(_width_) BITWIDTH_SUFFIX(encode_bit_cluster_tree, _width_)
#define encode_bit_cluster_tree encode_bit_cluster_tree_(BITWIDTH)
#define vtenc_encode_(_width_) BITWIDTH_SUFFIX(vtenc_encode, _width_)
#define vtenc_encode vtenc_encode_(BITWIDTH)
#define vtenc_max_encoded_size_(_width_) BITWIDTH_SUFFIX(vtenc_max_encoded_size, _width_)
#define vtenc_max_encoded_size vtenc_max_encoded_size_(BITWIDTH)

#define enc_return_with_code(ctx, enc, code)  \
do {                                          \
  (enc)->last_error_code = code;              \
  encctx_close((ctx));                        \
  return 0;                                   \
} while (0)

#define enc_return_on_error(ctx, enc, exp)  \
do {                                        \
  const int code = (exp);                   \
  if (code != VTENC_OK) {                   \
    enc_return_with_code(ctx, enc, code);   \
  }                                         \
} while(0)

struct encctx {
  const TYPE        *values;
  size_t            values_len;
  int               skip_full_subtrees;
  size_t            min_cluster_length;
  struct enc_stack  stack;
  struct bswriter   bits_writer;
};

static int encctx_init(struct encctx *ctx,
  const VtencEncoder *enc, const TYPE *in, size_t in_len,
  uint8_t *out, size_t out_cap)
{
  ctx->values = in;
  ctx->values_len = in_len;

  /**
   * `skip_full_subtrees` parameter is only applicable to sets, i.e. sequences
   * with no repeated values.
   */
  ctx->skip_full_subtrees = !enc->allow_repeated_values && enc->skip_full_subtrees;

  ctx->min_cluster_length = enc->min_cluster_length;

  enc_stack_init(&ctx->stack);

  return bswriter_init(&(ctx->bits_writer), out, out_cap);
}

static inline size_t encctx_close(struct encctx *ctx)
{
  return bswriter_close(&(ctx->bits_writer));
}

static inline int encode_lower_bits_step(struct encctx *ctx,
  uint64_t value, unsigned int n_bits)
{
#if BITWIDTH > BIT_STREAM_MAX_WRITE
  if (n_bits > BIT_STREAM_MAX_WRITE) {
    return_if_error(bswriter_write(
      &(ctx->bits_writer),
      value & BITS_SIZE_MASK[BIT_STREAM_MAX_WRITE],
      BIT_STREAM_MAX_WRITE
    ));

    value >>= BIT_STREAM_MAX_WRITE;
    n_bits -= BIT_STREAM_MAX_WRITE;
  }
#endif

  return bswriter_write(&(ctx->bits_writer), value & BITS_SIZE_MASK[n_bits], n_bits);
}

static inline int encode_lower_bits(struct encctx *ctx,
  const TYPE *values, size_t values_len, unsigned int n_bits)
{
  size_t i;

  for (i = 0; i < values_len; ++i) {
    return_if_error(encode_lower_bits_step(ctx, values[i], n_bits));
  }

  return VTENC_OK;
}

static inline void bcltree_add(struct encctx *ctx,
  const struct enc_bit_cluster *cluster)
{
  if (cluster->bit_pos == 0)
    return;

  if (cluster->length == 0)
    return;

  enc_stack_push(&ctx->stack, cluster);
}

static inline int bcltree_has_more(struct encctx *ctx)
{
  return !enc_stack_empty(&ctx->stack);
}

static inline struct enc_bit_cluster *bcltree_next(struct encctx *ctx)
{
  return enc_stack_pop(&ctx->stack);
}

static int encode_bit_cluster_tree(struct encctx *ctx)
{
  bcltree_add(ctx, &(struct enc_bit_cluster){0, ctx->values_len, BITWIDTH});

  while (bcltree_has_more(ctx)) {
    struct enc_bit_cluster *cluster = bcltree_next(ctx);
    size_t cl_from = cluster->from;
    size_t cl_len = cluster->length;
    unsigned int cl_bit_pos = cluster->bit_pos;
    unsigned int cur_bit_pos = cl_bit_pos - 1;

    if (ctx->skip_full_subtrees && is_full_subtree(cl_len, cl_bit_pos))
      continue;

    if (cl_len <= ctx->min_cluster_length) {
      return_if_error(encode_lower_bits(ctx, ctx->values + cl_from, cl_len, cl_bit_pos));
      continue;
    }

    size_t n_zeros = count_zeros_at_bit_pos(ctx->values + cl_from, cl_len, cur_bit_pos);
    unsigned int enc_len = bits_len_u64(cl_len);
    return_if_error(bswriter_write(&(ctx->bits_writer), n_zeros, enc_len));

    {
      struct enc_bit_cluster zeros_cluster = {cl_from, n_zeros, cur_bit_pos};
      struct enc_bit_cluster ones_cluster = {cl_from + n_zeros, cl_len - n_zeros, cur_bit_pos};

      bcltree_add(ctx, &ones_cluster);
      bcltree_add(ctx, &zeros_cluster);
    }
  }

  return VTENC_OK;
}

size_t vtenc_encode(VtencEncoder *enc, const TYPE *in, size_t in_len,
  uint8_t *out, size_t out_cap)
{
  struct encctx ctx;
  uint64_t max_values = enc->allow_repeated_values ? LIST_MAX_VALUES : SET_MAX_VALUES;

  enc->last_error_code = VTENC_OK;

  enc_return_on_error(&ctx, enc,
    encctx_init(&ctx, enc, in, in_len, out, out_cap)
  );

  if ((uint64_t)in_len > max_values) {
    enc_return_with_code(&ctx, enc, VTENC_ERR_INPUT_TOO_BIG);
  }

  enc_return_on_error(&ctx, enc, encode_bit_cluster_tree(&ctx));

  return encctx_close(&ctx);
}

size_t vtenc_max_encoded_size(size_t in_len)
{
  return bswriter_align_buffer_size((BITWIDTH / 8) * (in_len + 1));
}
