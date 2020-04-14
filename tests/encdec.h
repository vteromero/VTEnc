/**
  Copyright (c) 2020 Vicente Romero Calero. All rights reserved.
  Licensed under the MIT License.
  See LICENSE file in the project root for full license information.
 */
#ifndef VTENC_TESTS_ENCDEC_H_
#define VTENC_TESTS_ENCDEC_H_

#include <stddef.h>
#include <stdint.h>

#include "../vtenc.h"

int test_encode_and_decode8(VtencEncoder *encoder, const uint8_t *in, size_t in_len, int show_summary);
int test_encode_and_decode16(VtencEncoder *encoder, const uint16_t *in, size_t in_len, int show_summary);
int test_encode_and_decode32(VtencEncoder *encoder, const uint32_t *in, size_t in_len, int show_summary);
int test_encode_and_decode64(VtencEncoder *encoder, const uint64_t *in, size_t in_len, int show_summary);

struct EncDecFuncs {
  size_t (*type_size)();
  size_t (*max_encoded_size)(const VtencEncoder *enc, size_t in_len);
  size_t (*encode)(VtencEncoder *enc, const void *in, size_t in_len, uint8_t *out, size_t out_cap);
  size_t (*decoded_size)(VtencDecoder *dec, const void *in, size_t in_len);
  void (*decode)(VtencDecoder *dec, const uint8_t *in, size_t in_len, void *out, size_t out_len);
};

struct EncDecCtx {
  const void *in;
  size_t in_len;
  uint8_t *enc_out;
  size_t enc_out_len;
  void *dec_out;
  size_t dec_out_len;
};

struct EncDec {
  int has_repeated_values;
  int skip_full_subtrees;
  struct EncDecCtx ctx;
  const struct EncDecFuncs *funcs;
};

void encdec_init(struct EncDec *encdec, const struct EncDecFuncs *funcs);
void encdec_init8(struct EncDec *encdec);
void encdec_init16(struct EncDec *encdec);
void encdec_init32(struct EncDec *encdec);
void encdec_init64(struct EncDec *encdec);
int encdec_encode(struct EncDec *encdec, const void *in, size_t in_len);
int encdec_decode(struct EncDec *encdec);
int encdec_check_equality(struct EncDec *encdec);
void encdec_print_summary(struct EncDec *encdec);
void encdec_free(struct EncDec *encdec);

#endif /* VTENC_TESTS_ENCDEC_H_ */
