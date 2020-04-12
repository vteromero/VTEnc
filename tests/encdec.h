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

int test_encode_and_decode8(VtencEncoder *encoder, const uint8_t *in, size_t in_len);
int test_encode_and_decode16(VtencEncoder *encoder, const uint16_t *in, size_t in_len);
int test_encode_and_decode32(VtencEncoder *encoder, const uint32_t *in, size_t in_len);
int test_encode_and_decode64(VtencEncoder *encoder, const uint64_t *in, size_t in_len);

#endif /* VTENC_TESTS_ENCDEC_H_ */
