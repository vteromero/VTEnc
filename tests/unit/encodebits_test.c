/**
  Copyright (c) 2022 Vicente Romero Calero. All rights reserved.
  Licensed under the MIT License.
  See LICENSE file in the project root for full license information.
 */
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "unit_tests.h"
#include "../../encodebits.h"

int test_encode_lower_bits8(void)
{
  const uint8_t values[] = {
    0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff
  };
  struct bswriter writer;
  const size_t buf_sz = 16;
  const size_t buf_cap = bswriter_align_buffer_size(buf_sz);
  uint8_t buf[buf_cap];

  memset(buf, 0, buf_cap);

  bswriter_init(&writer, buf, buf_cap);

  encode_lower_bits8(&writer, values, 8, 1);
  encode_lower_bits8(&writer, values, 8, 2);
  encode_lower_bits8(&writer, values, 8, 3);
  encode_lower_bits8(&writer, values, 4, 4);
  encode_lower_bits8(&writer, values, 4, 5);
  encode_lower_bits8(&writer, values, 2, 6);
  encode_lower_bits8(&writer, values, 2, 7);
  encode_lower_bits8(&writer, values, 2, 8);

  EXPECT_TRUE(
    memcmp(buf,
      "\xaa\xcc\xcc\x38\x8e\xe3\xf0\xf0"
      "\xe0\x83\x0f\xfc\x80\x3f\xc0\x3f", buf_sz) == 0
  );

  return 1;
}

int test_encode_lower_bits16(void)
{
  const uint16_t values[] = {
    0x0000, 0xffff, 0x0000, 0xffff,
    0x0000, 0xffff, 0x0000, 0xffff,
  };
  struct bswriter writer;
  const size_t buf_sz = 16;
  const size_t buf_cap = bswriter_align_buffer_size(buf_sz);
  uint8_t buf[buf_cap];

  memset(buf, 0, buf_cap);

  bswriter_init(&writer, buf, buf_cap);

  encode_lower_bits16(&writer, values, 8, 1);
  encode_lower_bits16(&writer, values, 8, 2);
  encode_lower_bits16(&writer, values, 8, 3);
  encode_lower_bits16(&writer, values, 4, 4);
  encode_lower_bits16(&writer, values, 4, 8);
  encode_lower_bits16(&writer, values, 2, 16);

  EXPECT_TRUE(
    memcmp(buf,
      "\xaa\xcc\xcc\x38\x8e\xe3\xf0\xf0"
      "\x00\xff\x00\xff\x00\x00\xff\xff", buf_sz) == 0
  );

  return 1;
}

int test_encode_lower_bits32(void)
{
  const uint32_t values[] = {
    0x00000000, 0xffffffff,
    0x00000000, 0xffffffff,
    0x00000000, 0xffffffff,
    0x00000000, 0xffffffff,
  };
  struct bswriter writer;
  const size_t buf_sz = 24;
  const size_t buf_cap = bswriter_align_buffer_size(buf_sz);
  uint8_t buf[buf_cap];

  memset(buf, 0, buf_cap);

  bswriter_init(&writer, buf, buf_cap);

  encode_lower_bits32(&writer, values, 8, 1);
  encode_lower_bits32(&writer, values, 8, 2);
  encode_lower_bits32(&writer, values, 8, 3);
  encode_lower_bits32(&writer, values, 4, 4);
  encode_lower_bits32(&writer, values, 4, 8);
  encode_lower_bits32(&writer, values, 2, 16);
  encode_lower_bits32(&writer, values, 2, 32);

  EXPECT_TRUE(
    memcmp(buf,
      "\xaa\xcc\xcc\x38\x8e\xe3\xf0\xf0"
      "\x00\xff\x00\xff\x00\x00\xff\xff"
      "\x00\x00\x00\x00\xff\xff\xff\xff", buf_sz) == 0
  );

  return 1;
}

int test_encode_lower_bits64(void)
{
  const uint64_t values[] = {
    0x0000000000000000,
    0xffffffffffffffff,
    0x0000000000000000,
    0xffffffffffffffff,
    0x0000000000000000,
    0xffffffffffffffff,
    0x0000000000000000,
    0xffffffffffffffff,
  };
  struct bswriter writer;
  const size_t buf_sz = 40;
  const size_t buf_cap = bswriter_align_buffer_size(buf_sz);
  uint8_t buf[buf_cap];

  memset(buf, 0, buf_cap);

  bswriter_init(&writer, buf, buf_cap);

  encode_lower_bits64(&writer, values, 8, 1);
  encode_lower_bits64(&writer, values, 8, 2);
  encode_lower_bits64(&writer, values, 8, 3);
  encode_lower_bits64(&writer, values, 4, 4);
  encode_lower_bits64(&writer, values, 4, 8);
  encode_lower_bits64(&writer, values, 2, 16);
  encode_lower_bits64(&writer, values, 2, 32);
  encode_lower_bits64(&writer, values, 2, 64);

  EXPECT_TRUE(
    memcmp(buf,
      "\xaa\xcc\xcc\x38\x8e\xe3\xf0\xf0"
      "\x00\xff\x00\xff\x00\x00\xff\xff"
      "\x00\x00\x00\x00\xff\xff\xff\xff"
      "\x00\x00\x00\x00\x00\x00\x00\x00"
      "\xff\xff\xff\xff\xff\xff\xff\xff", buf_sz) == 0
  );

  return 1;
}
