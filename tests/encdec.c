/**
  Copyright (c) 2020 Vicente Romero Calero. All rights reserved.
  Licensed under the MIT License.
  See LICENSE file in the project root for full license information.
 */
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "../vtenc.h"

int test_encode_and_decode8(VtencEncoder *encoder, const uint8_t *in, size_t in_len)
{
  size_t enc_out_cap, enc_out_len, dec_out_len;
  uint8_t *enc_out=NULL, *dec_out=NULL;
  int ret_code = 1;
  VtencDecoder decoder = {
    .has_repeated_values = encoder->has_repeated_values,
    .skip_full_subtrees = encoder->skip_full_subtrees
  };

  enc_out_cap = vtenc_max_encoded_size8(encoder, in_len);
  enc_out = (uint8_t *) malloc(enc_out_cap * sizeof(uint8_t));
  if (enc_out == NULL) {
    fprintf(stderr, "allocation error\n");
    ret_code = 0;
    goto free_and_exit;
  }

  enc_out_len = vtenc_encode8(encoder, in, in_len, enc_out, enc_out_cap);
  if (encoder->last_error_code != VtencErrorNoError) {
    fprintf(stderr, "encode failed with code: %d\n", encoder->last_error_code);
    ret_code = 0;
    goto free_and_exit;
  }

  dec_out_len = vtenc_decoded_size8(&decoder, enc_out, enc_out_len);
  if (decoder.last_error_code != VtencErrorNoError) {
    fprintf(stderr, "getting decoded size failed with code: %d\n", decoder.last_error_code);
    ret_code = 0;
    goto free_and_exit;
  }

  dec_out = (uint8_t *) malloc(dec_out_len * sizeof(uint8_t));
  if (dec_out == NULL) {
    fprintf(stderr, "allocation error\n");
    ret_code = 0;
    goto free_and_exit;
  }

  vtenc_decode8(&decoder, enc_out, enc_out_len, dec_out, dec_out_len);
  if (decoder.last_error_code != VtencErrorNoError) {
    fprintf(stderr, "decode failed with code: %d\n", decoder.last_error_code);
    ret_code = 0;
    goto free_and_exit;
  }

  if ((dec_out_len != in_len) || (memcmp(in, dec_out, in_len * sizeof(uint8_t)) != 0)) {
    fprintf(stderr, "decoded output different from original input\n");
    ret_code = 0;
    goto free_and_exit;
  }

free_and_exit:
  if (enc_out != NULL) free(enc_out);
  if (dec_out != NULL) free(dec_out);

  return ret_code;
}

int test_encode_and_decode16(VtencEncoder *encoder, const uint16_t *in, size_t in_len)
{
  size_t enc_out_cap, enc_out_len, dec_out_len;
  uint8_t *enc_out = NULL;
  uint16_t *dec_out=NULL;
  int ret_code = 1;
  VtencDecoder decoder = {
    .has_repeated_values = encoder->has_repeated_values,
    .skip_full_subtrees = encoder->skip_full_subtrees
  };

  enc_out_cap = vtenc_max_encoded_size16(encoder, in_len);
  enc_out = (uint8_t *) malloc(enc_out_cap * sizeof(uint8_t));
  if (enc_out == NULL) {
    fprintf(stderr, "allocation error\n");
    ret_code = 0;
    goto free_and_exit;
  }

  enc_out_len = vtenc_encode16(encoder, in, in_len, enc_out, enc_out_cap);
  if (encoder->last_error_code != VtencErrorNoError) {
    fprintf(stderr, "encode failed with code: %d\n", encoder->last_error_code);
    ret_code = 0;
    goto free_and_exit;
  }

  dec_out_len = vtenc_decoded_size16(&decoder, enc_out, enc_out_len);
  if (decoder.last_error_code != VtencErrorNoError) {
    fprintf(stderr, "getting decoded size failed with code: %d\n", decoder.last_error_code);
    ret_code = 0;
    goto free_and_exit;
  }

  dec_out = (uint16_t *) malloc(dec_out_len * sizeof(uint16_t));
  if (dec_out == NULL) {
    fprintf(stderr, "allocation error\n");
    ret_code = 0;
    goto free_and_exit;
  }

  vtenc_decode16(&decoder, enc_out, enc_out_len, dec_out, dec_out_len);
  if (decoder.last_error_code != VtencErrorNoError) {
    fprintf(stderr, "decode failed with code: %d\n", decoder.last_error_code);
    ret_code = 0;
    goto free_and_exit;
  }

  if ((dec_out_len != in_len) || (memcmp(in, dec_out, in_len * sizeof(uint16_t)) != 0)) {
    fprintf(stderr, "decoded output different from original input\n");
    ret_code = 0;
    goto free_and_exit;
  }

free_and_exit:
  if (enc_out != NULL) free(enc_out);
  if (dec_out != NULL) free(dec_out);

  return ret_code;
}

int test_encode_and_decode32(VtencEncoder *encoder, const uint32_t *in, size_t in_len)
{
  size_t enc_out_cap, enc_out_len, dec_out_len;
  uint8_t *enc_out = NULL;
  uint32_t *dec_out=NULL;
  int ret_code = 1;
  VtencDecoder decoder = {
    .has_repeated_values = encoder->has_repeated_values,
    .skip_full_subtrees = encoder->skip_full_subtrees
  };

  enc_out_cap = vtenc_max_encoded_size32(encoder, in_len);
  enc_out = (uint8_t *) malloc(enc_out_cap * sizeof(uint8_t));
  if (enc_out == NULL) {
    fprintf(stderr, "allocation error\n");
    ret_code = 0;
    goto free_and_exit;
  }

  enc_out_len = vtenc_encode32(encoder, in, in_len, enc_out, enc_out_cap);
  if (encoder->last_error_code != VtencErrorNoError) {
    fprintf(stderr, "encode failed with code: %d\n", encoder->last_error_code);
    ret_code = 0;
    goto free_and_exit;
  }

  dec_out_len = vtenc_decoded_size32(&decoder, enc_out, enc_out_len);
  if (decoder.last_error_code != VtencErrorNoError) {
    fprintf(stderr, "getting decoded size failed with code: %d\n", decoder.last_error_code);
    ret_code = 0;
    goto free_and_exit;
  }

  dec_out = (uint32_t *) malloc(dec_out_len * sizeof(uint32_t));
  if (dec_out == NULL) {
    fprintf(stderr, "allocation error\n");
    ret_code = 0;
    goto free_and_exit;
  }

  vtenc_decode32(&decoder, enc_out, enc_out_len, dec_out, dec_out_len);
  if (decoder.last_error_code != VtencErrorNoError) {
    fprintf(stderr, "decode failed with code: %d\n", decoder.last_error_code);
    ret_code = 0;
    goto free_and_exit;
  }

  if ((dec_out_len != in_len) || (memcmp(in, dec_out, in_len * sizeof(uint32_t)) != 0)) {
    fprintf(stderr, "decoded output different from original input\n");
    ret_code = 0;
    goto free_and_exit;
  }

free_and_exit:
  if (enc_out != NULL) free(enc_out);
  if (dec_out != NULL) free(dec_out);

  return ret_code;
}

int test_encode_and_decode64(VtencEncoder *encoder, const uint64_t *in, size_t in_len)
{
  size_t enc_out_cap, enc_out_len, dec_out_len;
  uint8_t *enc_out = NULL;
  uint64_t *dec_out=NULL;
  int ret_code = 1;
  VtencDecoder decoder = {
    .has_repeated_values = encoder->has_repeated_values,
    .skip_full_subtrees = encoder->skip_full_subtrees
  };

  enc_out_cap = vtenc_max_encoded_size64(encoder, in_len);
  enc_out = (uint8_t *) malloc(enc_out_cap * sizeof(uint8_t));
  if (enc_out == NULL) {
    fprintf(stderr, "allocation error\n");
    ret_code = 0;
    goto free_and_exit;
  }

  enc_out_len = vtenc_encode64(encoder, in, in_len, enc_out, enc_out_cap);
  if (encoder->last_error_code != VtencErrorNoError) {
    fprintf(stderr, "encode failed with code: %d\n", encoder->last_error_code);
    ret_code = 0;
    goto free_and_exit;
  }

  dec_out_len = vtenc_decoded_size64(&decoder, enc_out, enc_out_len);
  if (decoder.last_error_code != VtencErrorNoError) {
    fprintf(stderr, "getting decoded size failed with code: %d\n", decoder.last_error_code);
    ret_code = 0;
    goto free_and_exit;
  }

  dec_out = (uint64_t *) malloc(dec_out_len * sizeof(uint64_t));
  if (dec_out == NULL) {
    fprintf(stderr, "allocation error\n");
    ret_code = 0;
    goto free_and_exit;
  }

  vtenc_decode64(&decoder, enc_out, enc_out_len, dec_out, dec_out_len);
  if (decoder.last_error_code != VtencErrorNoError) {
    fprintf(stderr, "decode failed with code: %d\n", decoder.last_error_code);
    ret_code = 0;
    goto free_and_exit;
  }

  if ((dec_out_len != in_len) || (memcmp(in, dec_out, in_len * sizeof(uint64_t)) != 0)) {
    fprintf(stderr, "decoded output different from original input\n");
    ret_code = 0;
    goto free_and_exit;
  }

free_and_exit:
  if (enc_out != NULL) free(enc_out);
  if (dec_out != NULL) free(dec_out);

  return ret_code;
}
