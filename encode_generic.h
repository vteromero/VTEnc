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
#define encctx_add_cluster(_width_) ADD_UINT_SUFFIX(encctx_add_cluster, _width_)
#define encctx_close(_width_) ADD_UINT_SUFFIX(encctx_close, _width_)
#define count_zeros_at_bit_pos(_width_) ADD_UINT_SUFFIX(count_zeros_at_bit_pos, _width_)
#define encode_bits_tree(_width_) ADD_UINT_SUFFIX(encode_bits_tree, _width_)
#define list_write_cardinality(_width_) ADD_UINT_SUFFIX(list_write_cardinality, _width_)
#define set_write_cardinality(_width_) ADD_UINT_SUFFIX(set_write_cardinality, _width_)
#define vtenc_list_encode(_width_) ADD_UINT_SUFFIX(vtenc_list_encode, _width_)
#define vtenc_set_encode(_width_) ADD_UINT_SUFFIX(vtenc_set_encode, _width_)
#define vtenc_list_max_encoded_size(_width_) ADD_UINT_SUFFIX(vtenc_list_max_encoded_size, _width_)
#define vtenc_set_max_encoded_size(_width_) ADD_UINT_SUFFIX(vtenc_set_max_encoded_size, _width_)

#define ENCCTX_RETURN_ON_ERROR(ctx, exp) RETURN_IF_ERROR_WITH(exp, encctx_close(WIDTH)(&ctx))

struct EncodeCtx(WIDTH) {
  const TYPE *values;
  size_t values_len;
  unsigned int skip_full_subtrees;
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

VtencErrorCode vtenc_list_encode(WIDTH)(const TYPE *in, size_t in_len,
  uint8_t *out, size_t out_cap, size_t *out_len)
{
  struct EncodeCtx(WIDTH) ctx;

  if ((uint64_t)in_len > LIST_MAX_VALUES) return VtencErrorInputTooBig;

  ENCCTX_RETURN_ON_ERROR(ctx, encctx_init(WIDTH)(&ctx, in, in_len, out, out_cap));

  ENCCTX_RETURN_ON_ERROR(ctx, list_write_cardinality(WIDTH)(&ctx));

  ENCCTX_RETURN_ON_ERROR(ctx, encode_bits_tree(WIDTH)(&ctx));

  *out_len = encctx_close(WIDTH)(&ctx);

  return VtencErrorNoError;
}

VtencErrorCode vtenc_set_encode(WIDTH)(const TYPE *in, size_t in_len,
  uint8_t *out, size_t out_cap, size_t *out_len)
{
  struct EncodeCtx(WIDTH) ctx;

  if (in_len == 0) return VtencErrorInputTooSmall;
  if ((uint64_t)in_len > SET_MAX_VALUES) return VtencErrorInputTooBig;

  ENCCTX_RETURN_ON_ERROR(ctx, encctx_init(WIDTH)(&ctx, in, in_len, out, out_cap));

  ctx.skip_full_subtrees = 1;

  ENCCTX_RETURN_ON_ERROR(ctx, set_write_cardinality(WIDTH)(&ctx));

  ENCCTX_RETURN_ON_ERROR(ctx, encode_bits_tree(WIDTH)(&ctx));

  *out_len = encctx_close(WIDTH)(&ctx);

  return VtencErrorNoError;
}

size_t vtenc_list_max_encoded_size(WIDTH)(size_t in_len)
{
  return bswriter_align_buffer_size((LIST_CARDINALITY_SIZE / 8) + (WIDTH / 8) * (in_len + 1));
}

size_t vtenc_set_max_encoded_size(WIDTH)(size_t in_len)
{
  return bswriter_align_buffer_size((SET_CARDINALITY_SIZE / 8) + (WIDTH / 8) * (in_len + 1));
}
