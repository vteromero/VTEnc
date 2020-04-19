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

#define DecodeCtx(_width_) PASTE2(DecodeCtx, _width_)
#define decctx_init(_width_) WIDTH_SUFFIX(decctx_init, _width_)
#define decctx_init_with_decoder(_width_) WIDTH_SUFFIX(decctx_init_with_decoder, _width_)
#define decctx_add_cluster(_width_) WIDTH_SUFFIX(decctx_add_cluster, _width_)
#define decctx_close(_width_) WIDTH_SUFFIX(decctx_close, _width_)
#define decode_lower_bits(_width_) WIDTH_SUFFIX(decode_lower_bits, _width_)
#define decode_full_subtree(_width_) WIDTH_SUFFIX(decode_full_subtree, _width_)
#define set_ones_at_bit_pos(_width_) WIDTH_SUFFIX(set_ones_at_bit_pos, _width_)
#define decode_bits_tree(_width_) WIDTH_SUFFIX(decode_bits_tree, _width_)
#define list_read_cardinality(_width_) WIDTH_SUFFIX(list_read_cardinality, _width_)
#define set_read_cardinality(_width_) WIDTH_SUFFIX(set_read_cardinality, _width_)
#define vtenc_decode(_width_) WIDTH_SUFFIX(vtenc_decode, _width_)

#define DEC_RETURN_WITH_CODE(ctx, dec, code)  \
do {                                          \
  (dec)->last_error_code = code;              \
  decctx_close(WIDTH)((ctx));                 \
  return;                                     \
} while (0)

#define DEC_RETURN_ON_ERROR(ctx, dec, exp)  \
do {                                        \
  const VtencErrorCode code = (exp);        \
  if (code != VtencErrorNoError) {          \
    DEC_RETURN_WITH_CODE(ctx, dec, code);   \
  }                                         \
} while (0)

struct DecodeCtx(WIDTH) {
  TYPE *values;
  size_t values_len;
  int reconstruct_full_subtrees;
  struct BitClusterStack *cl_stack;
  BSReader bits_reader;
};

static VtencErrorCode decctx_init(WIDTH)(struct DecodeCtx(WIDTH) *ctx,
  const uint8_t *in, size_t in_len, TYPE *out, size_t out_len)
{
  ctx->values = out;
  ctx->values_len = out_len;

  ctx->reconstruct_full_subtrees = 0;

  ctx->cl_stack = bclstack_new(WIDTH);
  if (ctx->cl_stack == NULL) return VtencErrorMemoryAlloc;

  return bsreader_init(&(ctx->bits_reader), in, in_len);
}

static VtencErrorCode decctx_init_with_decoder(WIDTH)(struct DecodeCtx(WIDTH) *ctx,
  const VtencDecoder *dec, const uint8_t *in, size_t in_len, TYPE *out, size_t out_len)
{
  RETURN_IF_ERROR(decctx_init(WIDTH)(ctx, in, in_len, out, out_len));

  /**
   * `skip_full_subtrees` parameter is only applicable to sets, i.e. sequences
   * with no repeated values.
   */
  ctx->reconstruct_full_subtrees = !dec->allow_repeated_values && dec->skip_full_subtrees;

  return VtencErrorNoError;
}

static inline void decctx_add_cluster(WIDTH)(struct DecodeCtx(WIDTH) *ctx,
  size_t cl_from, size_t cl_len, unsigned int cl_bit_pos)
{
  if (cl_len == 0)
    return;

  bclstack_put(ctx->cl_stack, cl_from, cl_len, cl_bit_pos);
}

static inline void decctx_close(WIDTH)(struct DecodeCtx(WIDTH) *ctx)
{
  if (ctx->cl_stack != NULL) bclstack_free(&(ctx->cl_stack));
}

static inline VtencErrorCode decode_lower_bits(WIDTH)(struct DecodeCtx(WIDTH) *ctx,
  TYPE *value, unsigned int n_bits)
{
#if WIDTH == 64
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

static VtencErrorCode decode_bits_tree(WIDTH)(struct DecodeCtx(WIDTH) *ctx)
{
  struct BitCluster *cluster;
  size_t cl_from, cl_len;
  unsigned int cl_bit_pos, cur_bit_pos, enc_len;
  uint64_t n_zeros;

  decctx_add_cluster(WIDTH)(ctx, 0, ctx->values_len, WIDTH);

  while (!bclstack_empty(ctx->cl_stack)) {
    cluster = bclstack_get(ctx->cl_stack);
    cl_from = cluster->from;
    cl_len = cluster->length;
    cl_bit_pos = cluster->bit_pos;
    cur_bit_pos = cl_bit_pos - 1;

    if (cl_len == 1) {
      RETURN_IF_ERROR(decode_lower_bits(WIDTH)(ctx, ctx->values + cl_from, cl_bit_pos));
      continue;
    }

    if (ctx->reconstruct_full_subtrees && is_full_subtree(cl_len, cl_bit_pos)) {
      decode_full_subtree(WIDTH)(ctx->values + cl_from, cl_len);
      continue;
    }

    enc_len = bits_len_u64(cl_len);

    RETURN_IF_ERROR(bsreader_read(&(ctx->bits_reader), enc_len, &n_zeros));

    if (n_zeros > (uint64_t)cl_len) return VtencErrorWrongFormat;

    set_ones_at_bit_pos(WIDTH)(
      ctx->values + cl_from + n_zeros,
      cl_len - n_zeros,
      cur_bit_pos
    );

    if (cur_bit_pos == 0) continue;

    decctx_add_cluster(WIDTH)(ctx,
      cl_from,
      n_zeros,
      cur_bit_pos
    );
    decctx_add_cluster(WIDTH)(ctx,
      cl_from + n_zeros,
      cl_len - n_zeros,
      cur_bit_pos
    );
  }

  return VtencErrorNoError;
}

static VtencErrorCode list_read_cardinality(WIDTH)(BSReader *reader, uint64_t *cardinality)
{
  return bsreader_read(reader, LIST_CARDINALITY_SIZE, cardinality);
}

static VtencErrorCode set_read_cardinality(WIDTH)(BSReader *reader, uint64_t *cardinality)
{
  RETURN_IF_ERROR(bsreader_read(reader, SET_CARDINALITY_SIZE, cardinality));
  ++(*cardinality);
  return VtencErrorNoError;
}

void vtenc_decode(WIDTH)(VtencDecoder *dec, const uint8_t *in, size_t in_len,
  TYPE *out, size_t out_len)
{
  struct DecodeCtx(WIDTH) ctx;
  uint64_t max_values = dec->allow_repeated_values ? LIST_MAX_VALUES : SET_MAX_VALUES;
  uint64_t cardinality = 0;

  dec->last_error_code = VtencErrorNoError;

  memset(out, 0, out_len * sizeof(*out));

  DEC_RETURN_ON_ERROR(&ctx, dec,
    decctx_init_with_decoder(WIDTH)(&ctx, dec, in, in_len, out, out_len)
  );

  if (dec->allow_repeated_values) {
    DEC_RETURN_ON_ERROR(&ctx, dec,
      list_read_cardinality(WIDTH)(&(ctx.bits_reader), &cardinality)
    );
  } else {
    DEC_RETURN_ON_ERROR(&ctx, dec,
      set_read_cardinality(WIDTH)(&(ctx.bits_reader), &cardinality)
    );
  }

  if (cardinality > max_values || cardinality != (uint64_t)out_len) {
    DEC_RETURN_WITH_CODE(&ctx, dec, VtencErrorWrongFormat);
  }

  DEC_RETURN_ON_ERROR(&ctx, dec, decode_bits_tree(WIDTH)(&ctx));

  decctx_close(WIDTH)(&ctx);
}
