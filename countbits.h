/**
  Copyright (c) 2020 Vicente Romero Calero. All rights reserved.
  Licensed under the MIT License.
  See LICENSE file in the project root for full license information.
 */
#ifndef VTENC_COUNTBITS_H_
#define VTENC_COUNTBITS_H_

#include "bits.h"

#define BINSEARCH                                             \
do {                                                          \
  size_t half;                                                \
                                                              \
  if (values_len == 0) return 0;                              \
                                                              \
  while (values_len > 1) {                                    \
    half = values_len >> 1;                                   \
    base = ((base[half] & mask) == 0) ? &base[half] : base;   \
    values_len -= half;                                       \
  }                                                           \
                                                              \
  return ((*base & mask) == 0) + base - values;               \
} while (0)

static inline size_t count_zeros_at_bit_pos_u8(const uint8_t *values,
  size_t values_len, unsigned int bit_pos)
{
  const uint8_t mask = BITS_POS_MASK8[bit_pos];
  const uint8_t *base = values;
  BINSEARCH;
}

static inline size_t count_zeros_at_bit_pos_u16(const uint16_t *values,
  size_t values_len, unsigned int bit_pos)
{
  const uint16_t mask = BITS_POS_MASK16[bit_pos];
  const uint16_t *base = values;
  BINSEARCH;
}

static inline size_t count_zeros_at_bit_pos_u32(const uint32_t *values,
  size_t values_len, unsigned int bit_pos)
{
  const uint32_t mask = BITS_POS_MASK32[bit_pos];
  const uint32_t *base = values;
  BINSEARCH;
}

static inline size_t count_zeros_at_bit_pos_u64(const uint64_t *values,
  size_t values_len, unsigned int bit_pos)
{
  const uint64_t mask = BITS_POS_MASK64[bit_pos];
  const uint64_t *base = values;
  BINSEARCH;
}

#endif /* VTENC_COUNTBITS_H_ */
