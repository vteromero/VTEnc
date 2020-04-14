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
#define encctx_init(_width_) ADD_UINT_SUFFIX(encctx_init, _width_)
#define encctx_init_with_encoder(_width_) ADD_UINT_SUFFIX(encctx_init_with_encoder, _width_)
#define encctx_add_cluster(_width_) ADD_UINT_SUFFIX(encctx_add_cluster, _width_)
#define encctx_close(_width_) ADD_UINT_SUFFIX(encctx_close, _width_)
#define count_zeros_at_bit_pos(_width_) ADD_UINT_SUFFIX(count_zeros_at_bit_pos, _width_)
#define encode_lower_bits(_width_) ADD_UINT_SUFFIX(encode_lower_bits, _width_)
#define encode_bits_tree(_width_) ADD_UINT_SUFFIX(encode_bits_tree, _width_)
#define list_write_cardinality(_width_) ADD_UINT_SUFFIX(list_write_cardinality, _width_)
#define set_write_cardinality(_width_) ADD_UINT_SUFFIX(set_write_cardinality, _width_)
#define vtenc_encode(_width_) WIDTH_SUFFIX(vtenc_encode, _width_)
#define vtenc_max_encoded_size(_width_) WIDTH_SUFFIX(vtenc_max_encoded_size, _width_)

#define ENC_HANDLE_ERROR(ctx, enc, exp) \
do {                                    \
  const VtencErrorCode code = (exp);    \
  if (code != VtencErrorNoError) {      \
    (enc)->last_error_code = code;      \
    encctx_close(WIDTH)((ctx));         \
    return 0;                           \
  }                                     \
} while(0)

struct EncodeCtx(WIDTH) {
  const TYPE *values;
  size_t values_len;
  int skip_full_subtrees;
  struct BitClusterStack *cl_stack;
  BSWriter bits_writer;
};

static VtencErrorCode encctx_init(WIDTH)(struct EncodeCtx(WIDTH) *ctx,
  const TYPE *in, size_t in_len, uint8_t *out, size_t out_cap)
{
  ctx->values = in;
  ctx->values_len = in_len;

  ctx->skip_full_subtrees = 0;

  ctx->cl_stack = bclstack_new(WIDTH);
  if (ctx->cl_stack == NULL) return VtencErrorMemoryAlloc;

  return bswriter_init(&(ctx->bits_writer), out, out_cap);
}

static VtencErrorCode encctx_init_with_encoder(WIDTH)(struct EncodeCtx(WIDTH) *ctx,
  const VtencEncoder *enc, const TYPE *in, size_t in_len, uint8_t *out, size_t out_cap)
{
  RETURN_IF_ERROR(encctx_init(WIDTH)(ctx, in, in_len, out, out_cap));

  ctx->skip_full_subtrees = !enc->has_repeated_values && enc->skip_full_subtrees;

  return VtencErrorNoError;
}

static inline void encctx_add_cluster(WIDTH)(struct EncodeCtx(WIDTH) *ctx,
  size_t cl_from, size_t cl_len, unsigned int cl_bit_pos)
{
  if (cl_len == 0)
    return;

  if (ctx->skip_full_subtrees && is_full_subtree(cl_len, cl_bit_pos))
    return;

  bclstack_put(ctx->cl_stack, cl_from, cl_len, cl_bit_pos);
}

static inline size_t encctx_close(WIDTH)(struct EncodeCtx(WIDTH) *ctx)
{
  if (ctx->cl_stack != NULL) bclstack_free(&(ctx->cl_stack));

  return bswriter_close(&(ctx->bits_writer));
}

static inline VtencErrorCode encode_lower_bits(WIDTH)(struct EncodeCtx(WIDTH) *ctx,
  uint64_t value, unsigned int n_bits)
{
#if WIDTH == 64
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

static VtencErrorCode encode_bits_tree(WIDTH)(struct EncodeCtx(WIDTH) *ctx)
{
  struct BitCluster *cluster;
  size_t cl_from, cl_len, n_zeros;
  unsigned int cl_bit_pos, cur_bit_pos, enc_len;

  encctx_add_cluster(WIDTH)(ctx, 0, ctx->values_len, WIDTH);

  while (!bclstack_empty(ctx->cl_stack)) {
    cluster = bclstack_get(ctx->cl_stack);
    cl_from = cluster->from;
    cl_len = cluster->length;
    cl_bit_pos = cluster->bit_pos;
    cur_bit_pos = cl_bit_pos - 1;

    if (cl_len == 1) {
      RETURN_IF_ERROR(encode_lower_bits(WIDTH)(ctx, *(ctx->values + cl_from), cl_bit_pos));
      continue;
    }

    n_zeros = count_zeros_at_bit_pos(WIDTH)(
      ctx->values + cl_from,
      cl_len,
      cur_bit_pos
    );
    enc_len = bits_len_u64(cl_len);

    RETURN_IF_ERROR(bswriter_write(&(ctx->bits_writer), n_zeros, enc_len));

    if (cur_bit_pos == 0) continue;

    encctx_add_cluster(WIDTH)(ctx,
      cl_from,
      n_zeros,
      cur_bit_pos
    );
    encctx_add_cluster(WIDTH)(ctx,
      cl_from + n_zeros,
      cl_len - n_zeros,
      cur_bit_pos
    );
  }

  return VtencErrorNoError;
}

static VtencErrorCode list_write_cardinality(WIDTH)(struct EncodeCtx(WIDTH) *ctx)
{
  return bswriter_write(&(ctx->bits_writer), ctx->values_len, LIST_CARDINALITY_SIZE);
}

static VtencErrorCode set_write_cardinality(WIDTH)(struct EncodeCtx(WIDTH) *ctx)
{
  return bswriter_write(&(ctx->bits_writer), ctx->values_len - 1, SET_CARDINALITY_SIZE);
}

size_t vtenc_encode(WIDTH)(VtencEncoder *enc, const TYPE *in, size_t in_len,
  uint8_t *out, size_t out_cap)
{
  struct EncodeCtx(WIDTH) ctx;
  uint64_t max_values = enc->has_repeated_values ? LIST_MAX_VALUES : SET_MAX_VALUES;

  enc->last_error_code = VtencErrorNoError;

  if ((uint64_t)in_len > max_values) {
    enc->last_error_code = VtencErrorInputTooBig;
    return 0;
  }

  if (!enc->has_repeated_values && in_len == 0) {
    enc->last_error_code = VtencErrorInputTooSmall;
    return 0;
  }

  ENC_HANDLE_ERROR(&ctx, enc,
    encctx_init_with_encoder(WIDTH)(&ctx, enc, in, in_len, out, out_cap)
  );

  if (enc->has_repeated_values) {
    ENC_HANDLE_ERROR(&ctx, enc, list_write_cardinality(WIDTH)(&ctx));
  } else {
    ENC_HANDLE_ERROR(&ctx, enc, set_write_cardinality(WIDTH)(&ctx));
  }

  ENC_HANDLE_ERROR(&ctx, enc, encode_bits_tree(WIDTH)(&ctx));

  return encctx_close(WIDTH)(&ctx);
}

size_t vtenc_max_encoded_size(WIDTH)(const VtencEncoder *enc, size_t in_len)
{
  if (enc->has_repeated_values) {
    return bswriter_align_buffer_size((LIST_CARDINALITY_SIZE / 8) + (WIDTH / 8) * (in_len + 1));
  } else {
    return bswriter_align_buffer_size((SET_CARDINALITY_SIZE / 8) + (WIDTH / 8) * (in_len + 1));
  }
}
