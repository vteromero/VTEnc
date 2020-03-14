/**
  Copyright (c) 2020 Vicente Romero Calero. All rights reserved.
  Licensed under the MIT License.
  See LICENSE file in the project root for full license information.
 */
#include <stdint.h>

#include "unit_tests.h"
#include "../../countbits.h"

int test_count_zeros_at_bit_pos_u8(void)
{
  const uint8_t values[] = {
    0,
    0,
    0,
    0,
    0,
    1<<0 | 1<<4,
    1<<0 | 1<<4,
    1<<0 | 1<<4,
    1<<0 | 1<<4,
    1<<0 | 1<<4
  };

  EXPECT_TRUE(count_zeros_at_bit_pos_u8(values, 0, 0) == 0);
  EXPECT_TRUE(count_zeros_at_bit_pos_u8(values, 0, 4) == 0);

  EXPECT_TRUE(count_zeros_at_bit_pos_u8(values, 3, 0) == 3);
  EXPECT_TRUE(count_zeros_at_bit_pos_u8(values, 3, 4) == 3);

  EXPECT_TRUE(count_zeros_at_bit_pos_u8(values, 10, 0) == 5);
  EXPECT_TRUE(count_zeros_at_bit_pos_u8(values, 10, 4) == 5);

  EXPECT_TRUE(count_zeros_at_bit_pos_u8(values + 3, 7, 0) == 2);
  EXPECT_TRUE(count_zeros_at_bit_pos_u8(values + 3, 7, 4) == 2);

  EXPECT_TRUE(count_zeros_at_bit_pos_u8(values + 5, 5, 0) == 0);
  EXPECT_TRUE(count_zeros_at_bit_pos_u8(values + 5, 5, 4) == 0);

  return 1;
}

int test_count_zeros_at_bit_pos_u16(void)
{
  const uint16_t values[] = {
    0,
    0,
    0,
    0,
    0,
    1<<0 | 1<<8,
    1<<0 | 1<<8,
    1<<0 | 1<<8,
    1<<0 | 1<<8,
    1<<0 | 1<<8
  };

  EXPECT_TRUE(count_zeros_at_bit_pos_u16(values, 0, 0) == 0);
  EXPECT_TRUE(count_zeros_at_bit_pos_u16(values, 0, 8) == 0);

  EXPECT_TRUE(count_zeros_at_bit_pos_u16(values, 3, 0) == 3);
  EXPECT_TRUE(count_zeros_at_bit_pos_u16(values, 3, 8) == 3);

  EXPECT_TRUE(count_zeros_at_bit_pos_u16(values, 10, 0) == 5);
  EXPECT_TRUE(count_zeros_at_bit_pos_u16(values, 10, 8) == 5);

  EXPECT_TRUE(count_zeros_at_bit_pos_u16(values + 3, 7, 0) == 2);
  EXPECT_TRUE(count_zeros_at_bit_pos_u16(values + 3, 7, 8) == 2);

  EXPECT_TRUE(count_zeros_at_bit_pos_u16(values + 5, 5, 0) == 0);
  EXPECT_TRUE(count_zeros_at_bit_pos_u16(values + 5, 5, 8) == 0);

  return 1;
}

int test_count_zeros_at_bit_pos_u32(void)
{
  const uint32_t values[] = {
    0,
    0,
    0,
    0,
    0,
    1<<0 | 1<<16,
    1<<0 | 1<<16,
    1<<0 | 1<<16,
    1<<0 | 1<<16,
    1<<0 | 1<<16
  };

  EXPECT_TRUE(count_zeros_at_bit_pos_u32(values, 0, 0) == 0);
  EXPECT_TRUE(count_zeros_at_bit_pos_u32(values, 0, 16) == 0);

  EXPECT_TRUE(count_zeros_at_bit_pos_u32(values, 3, 0) == 3);
  EXPECT_TRUE(count_zeros_at_bit_pos_u32(values, 3, 16) == 3);

  EXPECT_TRUE(count_zeros_at_bit_pos_u32(values, 10, 0) == 5);
  EXPECT_TRUE(count_zeros_at_bit_pos_u32(values, 10, 16) == 5);

  EXPECT_TRUE(count_zeros_at_bit_pos_u32(values + 3, 7, 0) == 2);
  EXPECT_TRUE(count_zeros_at_bit_pos_u32(values + 3, 7, 16) == 2);

  EXPECT_TRUE(count_zeros_at_bit_pos_u32(values + 5, 5, 0) == 0);
  EXPECT_TRUE(count_zeros_at_bit_pos_u32(values + 5, 5, 16) == 0);

  return 1;
}

int test_count_zeros_at_bit_pos_u64(void)
{
  const uint64_t values[] = {
    0ULL,
    0ULL,
    0ULL,
    0ULL,
    0ULL,
    1ULL<<0 | 1ULL<<32,
    1ULL<<0 | 1ULL<<32,
    1ULL<<0 | 1ULL<<32,
    1ULL<<0 | 1ULL<<32,
    1ULL<<0 | 1ULL<<32
  };

  EXPECT_TRUE(count_zeros_at_bit_pos_u64(values, 0, 0) == 0);
  EXPECT_TRUE(count_zeros_at_bit_pos_u64(values, 0, 32) == 0);

  EXPECT_TRUE(count_zeros_at_bit_pos_u64(values, 3, 0) == 3);
  EXPECT_TRUE(count_zeros_at_bit_pos_u64(values, 3, 32) == 3);

  EXPECT_TRUE(count_zeros_at_bit_pos_u64(values, 10, 0) == 5);
  EXPECT_TRUE(count_zeros_at_bit_pos_u64(values, 10, 32) == 5);

  EXPECT_TRUE(count_zeros_at_bit_pos_u64(values + 3, 7, 0) == 2);
  EXPECT_TRUE(count_zeros_at_bit_pos_u64(values + 3, 7, 32) == 2);

  EXPECT_TRUE(count_zeros_at_bit_pos_u64(values + 5, 5, 0) == 0);
  EXPECT_TRUE(count_zeros_at_bit_pos_u64(values + 5, 5, 32) == 0);

  return 1;
}
