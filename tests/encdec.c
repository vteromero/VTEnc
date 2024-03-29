/**
  Copyright (c) 2020 Vicente Romero Calero. All rights reserved.
  Licensed under the MIT License.
  See LICENSE file in the project root for full license information.
 */
#include "encdec.h"

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "../vtenc.h"

static size_t type_size8() { return sizeof(uint8_t); }
static size_t type_size16() { return sizeof(uint16_t); }
static size_t type_size32() { return sizeof(uint32_t); }
static size_t type_size64() { return sizeof(uint64_t); }

static const struct EncDecFuncs enc_dec_8_funcs = {
  .type_size        = type_size8,
  .max_encoded_size = vtenc_max_encoded_size8,
  .encode           = (encode_func_t)vtenc_encode8,
  .decode           = (decode_func_t)vtenc_decode8
};

static const struct EncDecFuncs enc_dec_16_funcs = {
  .type_size        = type_size16,
  .max_encoded_size = vtenc_max_encoded_size16,
  .encode           = (encode_func_t)vtenc_encode16,
  .decode           = (decode_func_t)vtenc_decode16
};

static const struct EncDecFuncs enc_dec_32_funcs = {
  .type_size        = type_size32,
  .max_encoded_size = vtenc_max_encoded_size32,
  .encode           = (encode_func_t)vtenc_encode32,
  .decode           = (decode_func_t)vtenc_decode32
};

static const struct EncDecFuncs enc_dec_64_funcs = {
  .type_size        = type_size64,
  .max_encoded_size = vtenc_max_encoded_size64,
  .encode           = (encode_func_t)vtenc_encode64,
  .decode           = (decode_func_t)vtenc_decode64
};

static void encdecctx_init(struct EncDecCtx *ctx)
{
  ctx->in           = NULL;
  ctx->in_len       = 0;
  ctx->enc_out      = NULL;
  ctx->enc_out_len  = 0;
  ctx->dec_out      = NULL;
  ctx->dec_out_len  = 0;
}

void encdec_init(struct EncDec *encdec, const struct EncDecFuncs *funcs)
{
  encdec->allow_repeated_values = 1;
  encdec->skip_full_subtrees    = 1;
  encdec->min_cluster_length    = 1;
  encdec->funcs                 = funcs;
  encdecctx_init(&(encdec->ctx));
}

void encdec_init8(struct EncDec *encdec)
{
  encdec_init(encdec, &enc_dec_8_funcs);
}

void encdec_init16(struct EncDec *encdec)
{
  encdec_init(encdec, &enc_dec_16_funcs);
}

void encdec_init32(struct EncDec *encdec)
{
  encdec_init(encdec, &enc_dec_32_funcs);
}

void encdec_init64(struct EncDec *encdec)
{
  encdec_init(encdec, &enc_dec_64_funcs);
}

int encdec_encode(struct EncDec *encdec, const void *in, size_t in_len)
{
  size_t enc_out_cap;
  int rc, res=1;
  vtenc *encoder = vtenc_create();

  if (encoder == NULL) {
    fprintf(stderr, "failed to create the encoder\n");
    return 0;
  }

  vtenc_config(encoder, VTENC_CONFIG_ALLOW_REPEATED_VALUES, encdec->allow_repeated_values);
  vtenc_config(encoder, VTENC_CONFIG_SKIP_FULL_SUBTREES, encdec->skip_full_subtrees);
  vtenc_config(encoder, VTENC_CONFIG_MIN_CLUSTER_LENGTH, encdec->min_cluster_length);

  encdec->ctx.in = in;
  encdec->ctx.in_len = in_len;

  enc_out_cap = encdec->funcs->max_encoded_size(in_len);

  encdec->ctx.enc_out = (uint8_t *) malloc(enc_out_cap * sizeof(uint8_t));
  if (encdec->ctx.enc_out == NULL) {
    fprintf(stderr, "allocation error\n");
    res = 0;
    goto destroy_and_return;
  }

  rc = encdec->funcs->encode(
    encoder,
    encdec->ctx.in,
    encdec->ctx.in_len,
    encdec->ctx.enc_out,
    enc_out_cap
  );
  if (rc != VTENC_OK) {
    fprintf(stderr, "encode failed with code: %d\n", rc);
    res = 0;
    goto destroy_and_return;
  }

  encdec->ctx.enc_out_len = vtenc_encoded_size(encoder);

destroy_and_return:
  vtenc_destroy(encoder);

  return res;
}

int encdec_decode(struct EncDec *encdec)
{
  int rc, res=1;
  vtenc *decoder = vtenc_create();

  if (decoder == NULL) {
    fprintf(stderr, "failed to create the decoder\n");
    return 0;
  }

  vtenc_config(decoder, VTENC_CONFIG_ALLOW_REPEATED_VALUES, encdec->allow_repeated_values);
  vtenc_config(decoder, VTENC_CONFIG_SKIP_FULL_SUBTREES, encdec->skip_full_subtrees);
  vtenc_config(decoder, VTENC_CONFIG_MIN_CLUSTER_LENGTH, encdec->min_cluster_length);

  encdec->ctx.dec_out_len = encdec->ctx.in_len;

  encdec->ctx.dec_out = malloc(encdec->ctx.dec_out_len * encdec->funcs->type_size());

  if (encdec->ctx.dec_out == NULL) {
    fprintf(stderr, "allocation error\n");
    res = 0;
    goto destroy_and_return;
  }

  rc = encdec->funcs->decode(
    decoder,
    encdec->ctx.enc_out,
    encdec->ctx.enc_out_len,
    encdec->ctx.dec_out,
    encdec->ctx.dec_out_len
  );

  if (rc != VTENC_OK) {
    fprintf(stderr, "decode failed with code: %d\n", rc);
    res = 0;
    goto destroy_and_return;
  }

destroy_and_return:
  vtenc_destroy(decoder);

  return res;
}

int encdec_check_equality(struct EncDec *encdec)
{
  if (encdec->ctx.dec_out_len != encdec->ctx.in_len) {
    fprintf(stderr, "decoded output different from original input\n");
    return 0;
  }

  if (memcmp(encdec->ctx.in, encdec->ctx.dec_out, encdec->ctx.in_len * encdec->funcs->type_size()) != 0) {
    fprintf(stderr, "decoded output different from original input\n");
    return 0;
  }

  return 1;
}

void encdec_print_summary(struct EncDec *encdec)
{
  size_t in_len_in_bytes = encdec->ctx.in_len * encdec->funcs->type_size();
  double ratio = in_len_in_bytes / (double)encdec->ctx.enc_out_len;

  printf("input size: %lu (%lu bytes)\n", encdec->ctx.in_len, in_len_in_bytes);
  printf("encoded size: %lu bytes\n", encdec->ctx.enc_out_len);
  printf("compression ratio: %.1f\n", ratio);
}

void encdec_free(struct EncDec *encdec)
{
  if (encdec->ctx.enc_out != NULL) free(encdec->ctx.enc_out);
  if (encdec->ctx.dec_out != NULL) free(encdec->ctx.dec_out);
}
