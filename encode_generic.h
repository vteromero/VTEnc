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

struct EncodeCtx(WIDTH) {
  const TYPE *values;
  size_t values_len;
  unsigned int skip_full_subtrees;
  struct BitClusterQueue *cl_queue;
  BSWriter bits_writer;
};

static VtencErrorCode encctx_init(WIDTH)(struct EncodeCtx(WIDTH) *ctx,
  const TYPE *in, size_t in_len, uint8_t *out, size_t out_cap)
{
  ctx->values = in;
  ctx->values_len = in_len;

  ctx->skip_full_subtrees = 0;

  ctx->cl_queue = bclqueue_new(in_len + WIDTH);
  if (ctx->cl_queue == NULL) return VtencErrorMemoryAlloc;

  return bswriter_init(&(ctx->bits_writer), out, out_cap);
}

static inline void encctx_add_cluster(WIDTH)(struct EncodeCtx(WIDTH) *ctx,
  size_t cl_from, size_t cl_len, unsigned int cl_bit_pos)
{
  if (cl_len == 0)
    return;

  if (ctx->skip_full_subtrees && is_full_subtree(cl_len, cl_bit_pos))
    return;

  bclqueue_put(ctx->cl_queue, cl_from, cl_len, cl_bit_pos);
}

static inline size_t encctx_close(WIDTH)(struct EncodeCtx(WIDTH) *ctx)
{
  bclqueue_free(&(ctx->cl_queue));

  return bswriter_close(&(ctx->bits_writer));
}

static inline size_t count_zeros_at_bit_pos(WIDTH)(const TYPE *values,
  size_t values_len, unsigned int bit_pos)
{
  const TYPE mask = (TYPE)1 << bit_pos;
  size_t l = 0;
  size_t r = values_len;
  size_t m, i;

  do {
    m = (r - l) / 2;
    i = l + m;
    if((values[i] & mask) == 0) {
      l = i;
    } else {
      r = i;
    }
  } while (m > 0);

  return r;
}

static VtencErrorCode encode_bits_tree(WIDTH)(struct EncodeCtx(WIDTH) *ctx)
{
  struct BitCluster *cluster;
  size_t n_zeros;
  unsigned int cur_bit_pos, enc_len;

  encctx_add_cluster(WIDTH)(ctx, 0, ctx->values_len, WIDTH);

  while (!bclqueue_empty(ctx->cl_queue)) {
    cluster = bclqueue_get(ctx->cl_queue);
    cur_bit_pos = cluster->bit_pos - 1;

    n_zeros = count_zeros_at_bit_pos(WIDTH)(
      ctx->values + cluster->from,
      cluster->length,
      cur_bit_pos
    );
    enc_len = bits_len_u64(cluster->length);

    RETURN_IF_ERROR(bswriter_write(&(ctx->bits_writer), n_zeros, enc_len));

    if (cur_bit_pos == 0) continue;

    encctx_add_cluster(WIDTH)(ctx,
      cluster->from,
      n_zeros,
      cur_bit_pos
    );
    encctx_add_cluster(WIDTH)(ctx,
      cluster->from + n_zeros,
      cluster->length - n_zeros,
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

  RETURN_IF_ERROR(encctx_init(WIDTH)(&ctx, in, in_len, out, out_cap));

  RETURN_IF_ERROR(list_write_cardinality(WIDTH)(&ctx));

  RETURN_IF_ERROR(encode_bits_tree(WIDTH)(&ctx));

  *out_len = encctx_close(WIDTH)(&ctx);

  return VtencErrorNoError;
}

VtencErrorCode vtenc_set_encode(WIDTH)(const TYPE *in, size_t in_len,
  uint8_t *out, size_t out_cap, size_t *out_len)
{
  struct EncodeCtx(WIDTH) ctx;

  if (in_len == 0) return VtencErrorInputTooSmall;
  if ((uint64_t)in_len > SET_MAX_VALUES) return VtencErrorInputTooBig;

  RETURN_IF_ERROR(encctx_init(WIDTH)(&ctx, in, in_len, out, out_cap));

  ctx.skip_full_subtrees = 1;

  RETURN_IF_ERROR(set_write_cardinality(WIDTH)(&ctx));

  RETURN_IF_ERROR(encode_bits_tree(WIDTH)(&ctx));

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
