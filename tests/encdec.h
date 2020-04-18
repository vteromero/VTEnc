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

typedef size_t (*type_size_func_t)();
typedef size_t (*max_encoded_size_func_t)(size_t);
typedef size_t (*encode_func_t)(VtencEncoder *, const void *, size_t,  uint8_t *, size_t);
typedef size_t (*decoded_size_func_t)(VtencDecoder *, const void *, size_t);
typedef void (*decode_func_t)(VtencDecoder *, const uint8_t *, size_t,  void *, size_t);

struct EncDecFuncs {
  type_size_func_t type_size;
  max_encoded_size_func_t max_encoded_size;
  encode_func_t encode;
  decoded_size_func_t decoded_size;
  decode_func_t decode;
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
  int allow_repeated_values;
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
