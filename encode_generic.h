/**
  Copyright (c) 2019 Vicente Romero Calero. All rights reserved.
  Licensed under the MIT License.
  See LICENSE file in the project root for full license information.
 */
#include <assert.h>
#include <stddef.h>
#include <stdint.h>

#include "bitcluster.h"
#include "bitstream.h"
#include "common.h"
#include "countbits.h"
#include "error.h"
#include "internals.h"

#define EncodeCtx(_width_) PASTE2(EncodeCtx, _width_)
#define encctx_init(_width_) WIDTH_SUFFIX(encctx_init, _width_)
#define encctx_close(_width_) WIDTH_SUFFIX(encctx_close, _width_)
#define count_zeros_at_bit_pos(_width_) WIDTH_SUFFIX(count_zeros_at_bit_pos, _width_)
#define encode_lower_bits_step(_width_) WIDTH_SUFFIX(encode_lower_bits_step, _width_)
#define encode_lower_bits(_width_) WIDTH_SUFFIX(encode_lower_bits, _width_)
#define bcltree_add(_width_) WIDTH_SUFFIX(bcltree_add, _width_)
#define bcltree_visit(_width_) WIDTH_SUFFIX(bcltree_visit, _width_)
#define bcltree_has_more(_width_) WIDTH_SUFFIX(bcltree_has_more, _width_)
#define bcltree_next(_width_) WIDTH_SUFFIX(bcltree_next, _width_)
#define encode_bit_cluster_tree(_width_) WIDTH_SUFFIX(encode_bit_cluster_tree, _width_)
#define vtenc_encode(_width_) WIDTH_SUFFIX(vtenc_encode, _width_)
#define vtenc_max_encoded_size(_width_) WIDTH_SUFFIX(vtenc_max_encoded_size, _width_)

#define ENC_RETURN_WITH_CODE(ctx, enc, code)  \
do {                                          \
  (enc)->last_error_code = code;              \
  encctx_close(WIDTH)((ctx));                 \
  return 0;                                   \
} while (0)

#define ENC_RETURN_ON_ERROR(ctx, enc, exp)  \
do {                                        \
  const VtencErrorCode code = (exp);        \
  if (code != VtencErrorNoError) {          \
    ENC_RETURN_WITH_CODE(ctx, enc, code);   \
  }                                         \
} while(0)

struct EncodeCtx(WIDTH) {
  const TYPE              *values;
  size_t                  values_len;
  int                     skip_full_subtrees;
  size_t                  min_cluster_length;
  struct BitClusterStack  cl_stack;
  struct BSWriter         bits_writer;
};

static VtencErrorCode encctx_init(WIDTH)(struct EncodeCtx(WIDTH) *ctx,
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

  bclstack_init(&ctx->cl_stack);

  return bswriter_init(&(ctx->bits_writer), out, out_cap);
}

static inline size_t encctx_close(WIDTH)(struct EncodeCtx(WIDTH) *ctx)
{
  return bswriter_close(&(ctx->bits_writer));
}

static inline VtencErrorCode encode_lower_bits_step(WIDTH)(struct EncodeCtx(WIDTH) *ctx,
  uint64_t value, unsigned int n_bits)
{
#if WIDTH > BIT_STREAM_MAX_WRITE
  if (n_bits > BIT_STREAM_MAX_WRITE) {
    RETURN_IF_ERROR(bswriter_write(
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

static inline VtencErrorCode encode_lower_bits(WIDTH)(struct EncodeCtx(WIDTH) *ctx,
  const TYPE *values, size_t values_len, unsigned int n_bits)
{
  size_t i;

  for (i = 0; i < values_len; ++i) {
    RETURN_IF_ERROR(encode_lower_bits_step(WIDTH)(ctx, values[i], n_bits));
  }

  return VtencErrorNoError;
}

static inline void bcltree_add(WIDTH)(struct EncodeCtx(WIDTH) *ctx,
  size_t cl_from, size_t cl_len, unsigned int cl_bit_pos)
{
  if (cl_bit_pos == 0)
    return;

  if (cl_len == 0)
    return;

  bclstack_put(&ctx->cl_stack, cl_from, cl_len, cl_bit_pos);
}

static inline int bcltree_has_more(WIDTH)(struct EncodeCtx(WIDTH) *ctx)
{
  return !bclstack_empty(&ctx->cl_stack);
}

static inline struct BitCluster *bcltree_next(WIDTH)(struct EncodeCtx(WIDTH) *ctx)
{
  return bclstack_get(&ctx->cl_stack);
}

static VtencErrorCode encode_bit_cluster_tree(WIDTH)(struct EncodeCtx(WIDTH) *ctx)
{
  bcltree_add(WIDTH)(ctx, 0, ctx->values_len, WIDTH);

  while (bcltree_has_more(WIDTH)(ctx)) {
    struct BitCluster *cluster = bcltree_next(WIDTH)(ctx);
    size_t cl_from = cluster->from;
    size_t cl_len = cluster->length;
    unsigned int cl_bit_pos = cluster->bit_pos;
    unsigned int cur_bit_pos = cl_bit_pos - 1;

    if (ctx->skip_full_subtrees && is_full_subtree(cl_len, cl_bit_pos))
      continue;

    if (cl_len <= ctx->min_cluster_length) {
      RETURN_IF_ERROR(encode_lower_bits(WIDTH)(ctx, ctx->values + cl_from, cl_len, cl_bit_pos));
      continue;
    }

    size_t n_zeros = count_zeros_at_bit_pos(WIDTH)(ctx->values + cl_from, cl_len, cur_bit_pos);
    unsigned int enc_len = bits_len_u64(cl_len);
    RETURN_IF_ERROR(bswriter_write(&(ctx->bits_writer), n_zeros, enc_len));

    bcltree_add(WIDTH)(ctx, cl_from + n_zeros, cl_len - n_zeros, cur_bit_pos);
    bcltree_add(WIDTH)(ctx, cl_from, n_zeros, cur_bit_pos);
  }

  return VtencErrorNoError;
}

size_t vtenc_encode(WIDTH)(VtencEncoder *enc, const TYPE *in, size_t in_len,
  uint8_t *out, size_t out_cap)
{
  struct EncodeCtx(WIDTH) ctx;
  uint64_t max_values = enc->allow_repeated_values ? LIST_MAX_VALUES : SET_MAX_VALUES;

  enc->last_error_code = VtencErrorNoError;

  ENC_RETURN_ON_ERROR(&ctx, enc,
    encctx_init(WIDTH)(&ctx, enc, in, in_len, out, out_cap)
  );

  if ((uint64_t)in_len > max_values) {
    ENC_RETURN_WITH_CODE(&ctx, enc, VtencErrorInputTooBig);
  }

  ENC_RETURN_ON_ERROR(&ctx, enc, encode_bit_cluster_tree(WIDTH)(&ctx));

  return encctx_close(WIDTH)(&ctx);
}

size_t vtenc_max_encoded_size(WIDTH)(size_t in_len)
{
  return bswriter_align_buffer_size((WIDTH / 8) * (in_len + 1));
}
