/**
  Copyright (c) 2019 Vicente Romero Calero. All rights reserved.
  Licensed under the MIT License.
  See LICENSE file in the project root for full license information.
 */
#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include "unit_tests.h"
#include "../../vtenc.h"

int list_decode8_test(const uint8_t *in, size_t in_len,
  const uint8_t *expected_out, size_t expected_out_len)
{
  size_t out_len = vtenc_list_decoded_size_u8(in, in_len);
  uint8_t out[out_len];

  EXPECT_TRUE(vtenc_list_decode_u8(in, in_len, out, out_len) == VtencErrorNoError);
  EXPECT_TRUE(out_len == expected_out_len);
  EXPECT_TRUE(memcmp(out, expected_out, sizeof(out)) == 0);

  return 1;
}

int list_decode16_test(const uint8_t *in, size_t in_len,
  const uint16_t *expected_out, size_t expected_out_len)
{
  size_t out_len = vtenc_list_decoded_size_u16(in, in_len);
  uint16_t out[out_len];

  EXPECT_TRUE(vtenc_list_decode_u16(in, in_len, out, out_len) == VtencErrorNoError);
  EXPECT_TRUE(out_len == expected_out_len);
  EXPECT_TRUE(memcmp(out, expected_out, sizeof(out)) == 0);

  return 1;
}

int list_decode32_test(const uint8_t *in, size_t in_len,
  const uint32_t *expected_out, size_t expected_out_len)
{
  size_t out_len = vtenc_list_decoded_size_u32(in, in_len);
  uint32_t out[out_len];

  EXPECT_TRUE(vtenc_list_decode_u32(in, in_len, out, out_len) == VtencErrorNoError);
  EXPECT_TRUE(out_len == expected_out_len);
  EXPECT_TRUE(memcmp(out, expected_out, sizeof(out)) == 0);

  return 1;
}

int list_decode64_test(const uint8_t *in, size_t in_len,
  const uint64_t *expected_out, size_t expected_out_len)
{
  size_t out_len = vtenc_list_decoded_size_u64(in, in_len);
  uint64_t out[out_len];

  EXPECT_TRUE(vtenc_list_decode_u64(in, in_len, out, out_len) == VtencErrorNoError);
  EXPECT_TRUE(out_len == expected_out_len);
  EXPECT_TRUE(memcmp(out, expected_out, sizeof(out)) == 0);

  return 1;
}

int set_decode8_test(const uint8_t *in, size_t in_len,
  const uint8_t *expected_out, size_t expected_out_len)
{
  size_t out_len = vtenc_set_decoded_size_u8(in, in_len);
  uint8_t out[out_len];

  EXPECT_TRUE(vtenc_set_decode_u8(in, in_len, out, out_len) == VtencErrorNoError);
  EXPECT_TRUE(out_len == expected_out_len);
  EXPECT_TRUE(memcmp(out, expected_out, sizeof(out)) == 0);

  return 1;
}

int set_decode16_test(const uint8_t *in, size_t in_len,
  const uint16_t *expected_out, size_t expected_out_len)
{
  size_t out_len = vtenc_set_decoded_size_u16(in, in_len);
  uint16_t out[out_len];

  EXPECT_TRUE(vtenc_set_decode_u16(in, in_len, out, out_len) == VtencErrorNoError);
  EXPECT_TRUE(out_len == expected_out_len);
  EXPECT_TRUE(memcmp(out, expected_out, sizeof(out)) == 0);

  return 1;
}

int set_decode32_test(const uint8_t *in, size_t in_len,
  const uint32_t *expected_out, size_t expected_out_len)
{
  size_t out_len = vtenc_set_decoded_size_u32(in, in_len);
  uint32_t out[out_len];

  EXPECT_TRUE(vtenc_set_decode_u32(in, in_len, out, out_len) == VtencErrorNoError);
  EXPECT_TRUE(out_len == expected_out_len);
  EXPECT_TRUE(memcmp(out, expected_out, sizeof(out)) == 0);

  return 1;
}

int set_decode64_test(const uint8_t *in, size_t in_len,
  const uint64_t *expected_out, size_t expected_out_len)
{
  size_t out_len = vtenc_set_decoded_size_u64(in, in_len);
  uint64_t out[out_len];

  EXPECT_TRUE(vtenc_set_decode_u64(in, in_len, out, out_len) == VtencErrorNoError);
  EXPECT_TRUE(out_len == expected_out_len);
  EXPECT_TRUE(memcmp(out, expected_out, sizeof(out)) == 0);

  return 1;
}

int test_vtenc_list_decode_u8_1(void)
{
  const uint8_t in[] = {0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff};
  const size_t in_len = sizeof(in);
  size_t out_len = 1;
  uint8_t out[out_len];

  EXPECT_TRUE(vtenc_list_decode_u8(in, in_len, out, out_len) == VtencErrorWrongFormat);

  return 1;
}

int test_vtenc_list_decode_u8_2(void)
{
  const uint8_t in[] = {0x09, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
  const size_t in_len = sizeof(in);
  size_t out_len = 4;
  uint8_t out[out_len];

  EXPECT_TRUE(vtenc_list_decode_u8(in, in_len, out, out_len) == VtencErrorWrongFormat);

  return 1;
}

int test_vtenc_list_decode_u8_3(void)
{
  const uint8_t in[] = {0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0e};
  const size_t in_len = sizeof(in);
  size_t out_len = vtenc_list_decoded_size_u8(in, in_len);
  uint8_t out[out_len];

  EXPECT_TRUE(vtenc_list_decode_u8(in, in_len, out, out_len) == VtencErrorWrongFormat);

  return 1;
}

int test_vtenc_list_decode_u8_4(void)
{
  const uint8_t in[] = {0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x4c, 0x00};
  const size_t in_len = sizeof(in);
  const uint8_t expected_out[] = {38};
  const size_t expected_out_len = sizeof(expected_out);

  return list_decode8_test(in, in_len, expected_out, expected_out_len);
}

int test_vtenc_list_decode_u8_5(void)
{
  const uint8_t in[] = {
    0x0b, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 0xcd, 0x92, 0xab, 0xa2,
    0xcb, 0x72, 0x4e, 0xa8, 0x00
  };
  const size_t in_len = sizeof(in);
  const uint8_t expected_out[] = {5, 22, 23, 44, 62, 69, 109, 113, 178, 194, 206};
  const size_t expected_out_len = sizeof(expected_out);

  return list_decode8_test(in, in_len, expected_out, expected_out_len);
}

int test_vtenc_list_decode_u8_6(void)
{
  const uint8_t in[] = {
    0x09, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0e, 0x51, 0x1d, 0x08, 0x00,
    0xc0, 0x03
  };
  const size_t in_len = sizeof(in);
  const uint8_t expected_out[] = {57, 57, 57, 111, 111, 111, 111, 208, 208};
  const size_t expected_out_len = sizeof(expected_out);

  return list_decode8_test(in, in_len, expected_out, expected_out_len);
}

int test_vtenc_list_decode_u16_1(void)
{
  const uint8_t in[] = {0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff};
  const size_t in_len = sizeof(in);
  size_t out_len = 1;
  uint16_t out[out_len];

  EXPECT_TRUE(vtenc_list_decode_u16(in, in_len, out, out_len) == VtencErrorWrongFormat);

  return 1;
}

int test_vtenc_list_decode_u16_2(void)
{
  const uint8_t in[] = {0x09, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
  const size_t in_len = sizeof(in);
  size_t out_len = 4;
  uint16_t out[out_len];

  EXPECT_TRUE(vtenc_list_decode_u16(in, in_len, out, out_len) == VtencErrorWrongFormat);

  return 1;
}

int test_vtenc_list_decode_u16_3(void)
{
  const uint8_t in[] = {0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0e};
  const size_t in_len = sizeof(in);
  size_t out_len = vtenc_list_decoded_size_u16(in, in_len);
  uint16_t out[out_len];

  EXPECT_TRUE(vtenc_list_decode_u16(in, in_len, out, out_len) == VtencErrorWrongFormat);

  return 1;
}

int test_vtenc_list_decode_u16_4(void)
{
  const uint8_t in[] = {
    0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x4c, 0x6c, 0x00
  };
  const size_t in_len = sizeof(in);
  const uint16_t expected_out[] = {13862};
  const size_t expected_out_len = sizeof(expected_out) / sizeof(expected_out[0]);

  return list_decode16_test(in, in_len, expected_out, expected_out_len);
}

int test_vtenc_list_decode_u16_5(void)
{
  const uint8_t in[] = {
    0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xda, 0xe8, 0x70, 0xab, 0x8c,
    0x92, 0xc2, 0x80, 0xd7, 0xf4, 0x9b, 0xc5, 0x12, 0x01
  };
  const size_t in_len = sizeof(in);
  const uint16_t expected_out[] = {1099, 2227, 8102, 27654, 29001, 35511, 50083};
  const size_t expected_out_len = sizeof(expected_out) / sizeof(expected_out[0]);

  return list_decode16_test(in, in_len, expected_out, expected_out_len);
}

int test_vtenc_list_decode_u16_6(void)
{
  const uint8_t in[] = {
    0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0xa7, 0x2d, 0x8a, 0x02,
    0x6d, 0xf1, 0x33, 0xf3, 0x0c
  };
  const size_t in_len = sizeof(in);
  const uint16_t expected_out[] = {677, 677, 677, 8881, 8881, 8881, 8881, 8881};
  const size_t expected_out_len = sizeof(expected_out) / sizeof(expected_out[0]);

  return list_decode16_test(in, in_len, expected_out, expected_out_len);
}

int test_vtenc_list_decode_u32_1(void)
{
  const uint8_t in[] = {0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff};
  const size_t in_len = sizeof(in);
  size_t out_len = 1;
  uint32_t out[out_len];

  EXPECT_TRUE(vtenc_list_decode_u32(in, in_len, out, out_len) == VtencErrorWrongFormat);

  return 1;
}

int test_vtenc_list_decode_u32_2(void)
{
  const uint8_t in[] = {0x09, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
  const size_t in_len = sizeof(in);
  size_t out_len = 4;
  uint32_t out[out_len];

  EXPECT_TRUE(vtenc_list_decode_u32(in, in_len, out, out_len) == VtencErrorWrongFormat);

  return 1;
}

int test_vtenc_list_decode_u32_3(void)
{
  const uint8_t in[] = {0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0e};
  const size_t in_len = sizeof(in);
  size_t out_len = vtenc_list_decoded_size_u32(in, in_len);
  uint32_t out[out_len];

  EXPECT_TRUE(vtenc_list_decode_u32(in, in_len, out, out_len) == VtencErrorWrongFormat);

  return 1;
}

int test_vtenc_list_decode_u32_4(void)
{
  const uint8_t in[] = {
    0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xb2, 0x90, 0x9c, 0x56, 0x00
  };
  const size_t in_len = sizeof(in);
  const uint32_t expected_out[] = {726550617};
  const size_t expected_out_len = sizeof(expected_out) / sizeof(expected_out[0]);

  return list_decode32_test(in, in_len, expected_out, expected_out_len);
}

int test_vtenc_list_decode_u32_5(void)
{
  const uint8_t in[] = {
    0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x4a, 0x41, 0xf9, 0x44, 0x8b,
    0x6b, 0x08, 0x3a, 0x81, 0xc5, 0x90, 0x0e, 0x4a, 0xab, 0xd1, 0x3d, 0x92,
    0x53, 0x00, 0x00
  };
  const size_t in_len = sizeof(in);
  const uint32_t expected_out[] = {
    5348, 13089333, 88199704, 271008013, 1451881090
  };
  const size_t expected_out_len = sizeof(expected_out) / sizeof(expected_out[0]);

  return list_decode32_test(in, in_len, expected_out, expected_out_len);
}

int test_vtenc_list_decode_u32_6(void)
{
  const uint8_t in[] = {
    0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x6c, 0x53, 0x11, 0x54, 0x50,
    0x11, 0x55, 0x41, 0x90, 0x20, 0x41, 0x90, 0x20, 0x49, 0x90, 0x04, 0x40,
    0x10, 0x20, 0x00
  };
  const size_t in_len = sizeof(in);
  const uint32_t expected_out[] = {
    77865901, 77865901, 77865901, 77865901, 314976310, 314976310
  };
  const size_t expected_out_len = sizeof(expected_out) / sizeof(expected_out[0]);

  return list_decode32_test(in, in_len, expected_out, expected_out_len);
}

int test_vtenc_list_decode_u64_1(void)
{
  const uint8_t in[] = {0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff};
  const size_t in_len = sizeof(in);
  size_t out_len = 1;
  uint64_t out[out_len];

  EXPECT_TRUE(vtenc_list_decode_u64(in, in_len, out, out_len) == VtencErrorWrongFormat);

  return 1;
}

int test_vtenc_list_decode_u64_2(void)
{
  const uint8_t in[] = {0x09, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
  const size_t in_len = sizeof(in);
  size_t out_len = 4;
  uint64_t out[out_len];

  EXPECT_TRUE(vtenc_list_decode_u64(in, in_len, out, out_len) == VtencErrorWrongFormat);

  return 1;
}

int test_vtenc_list_decode_u64_3(void)
{
  const uint8_t in[] = {0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0e};
  const size_t in_len = sizeof(in);
  size_t out_len = vtenc_list_decoded_size_u64(in, in_len);
  uint64_t out[out_len];

  EXPECT_TRUE(vtenc_list_decode_u64(in, in_len, out, out_len) == VtencErrorWrongFormat);

  return 1;
}

int test_vtenc_list_decode_u64_4(void)
{
  const uint8_t in[] = {
    0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc2, 0x44, 0x88, 0xfd, 0x21,
    0x03, 0xef, 0x56, 0x01
  };
  const size_t in_len = sizeof(in);
  const uint64_t expected_out[] = {0xab778190fec42261ULL};
  const size_t expected_out_len = sizeof(expected_out) / sizeof(expected_out[0]);

  return list_decode64_test(in, in_len, expected_out, expected_out_len);
}

int test_vtenc_list_decode_u64_5(void)
{
  const uint8_t in[] = {
    0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x48, 0x92, 0x24, 0x49, 0x92,
    0x24, 0xc9, 0xa9, 0x6a, 0x8e, 0x3b, 0x96, 0x84, 0xff, 0xff, 0xff, 0xdd,
    0xa5, 0x0d, 0xfd, 0xab, 0xaa, 0xc1, 0x77, 0x2b, 0x4c, 0x25, 0x00
  };
  const size_t in_len = sizeof(in);
  const uint64_t expected_out[] = {
    0x12a6ULL, 0x8addf0ULL, 0xffa1b4bbULL, 0x21258ee39aaaULL
  };
  const size_t expected_out_len = sizeof(expected_out) / sizeof(expected_out[0]);

  return list_decode64_test(in, in_len, expected_out, expected_out_len);
}

int test_vtenc_list_decode_u64_6(void)
{
  const uint8_t in[] = {
    0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xda, 0xb6, 0x6d, 0xdb, 0xb6,
    0x6d, 0xdb, 0x4e, 0x45, 0x45, 0x45, 0x45, 0x45, 0x45, 0x45, 0x45, 0x45,
    0x45, 0xe5, 0xff, 0xff, 0x7f, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66,
    0x06
  };
  const size_t in_len = sizeof(in);
  const uint64_t expected_out[] = {
    0x55555555ULL, 0x55555555ULL, 0x55555555ULL, 0x111111111111ULL, 0x111111111111ULL
  };
  const size_t expected_out_len = sizeof(expected_out) / sizeof(expected_out[0]);

  return list_decode64_test(in, in_len, expected_out, expected_out_len);
}

int test_vtenc_set_decode_u8_1(void)
{
  const uint8_t in[] = {0x00};
  const size_t in_len = sizeof(in);
  size_t out_len = 0;
  uint8_t out[out_len];

  EXPECT_TRUE(vtenc_set_decode_u8(in, in_len, out, out_len) == VtencErrorWrongFormat);

  return 1;
}

int test_vtenc_set_decode_u8_2(void)
{
  const uint8_t in[] = {0x03, 0xff};
  const size_t in_len = sizeof(in);
  size_t out_len = vtenc_set_decoded_size_u8(in, in_len);
  uint8_t out[out_len];

  EXPECT_TRUE(vtenc_set_decode_u8(in, in_len, out, out_len) == VtencErrorWrongFormat);

  return 1;
}

int test_vtenc_set_decode_u8_3(void)
{
  const uint8_t in[] = {0xff};
  const size_t in_len = sizeof(in);
  const size_t expected_out_len = 256;
  uint8_t expected_out[expected_out_len];
  size_t i;

  for (i = 0; i < expected_out_len; ++i) expected_out[i] = (uint8_t)i;

  return set_decode8_test(in, in_len, expected_out, expected_out_len);
}

int test_vtenc_set_decode_u8_4(void)
{
  const uint8_t in[] = {0x00, 0x21};
  const size_t in_len = sizeof(in);
  const uint8_t expected_out[] = {33};
  const size_t expected_out_len = sizeof(expected_out);

  return set_decode8_test(in, in_len, expected_out, expected_out_len);
}

int test_vtenc_set_decode_u8_5(void)
{
  const uint8_t in[] = {0x0b, 0x48, 0x90, 0x44, 0x44, 0x04};
  const size_t in_len = sizeof(in);
  const uint8_t expected_out[] = {0, 1, 2, 3, 4, 5, 6, 7, 160, 161, 162, 163};
  const size_t expected_out_len = sizeof(expected_out);

  return set_decode8_test(in, in_len, expected_out, expected_out_len);
}

int test_vtenc_set_decode_u8_6(void)
{
  const uint8_t in[] = {0x05, 0x8c, 0xaa, 0x72, 0x14, 0xdd, 0x00};
  const size_t in_len = sizeof(in);
  const uint8_t expected_out[] = {13, 77, 88, 93, 149, 212};
  const size_t expected_out_len = sizeof(expected_out);

  return set_decode8_test(in, in_len, expected_out, expected_out_len);
}

int test_vtenc_set_decode_u16_1(void)
{
  const uint8_t in[] = {0x00, 0x00};
  const size_t in_len = sizeof(in);
  size_t out_len = 0;
  uint16_t out[out_len];

  EXPECT_TRUE(vtenc_set_decode_u16(in, in_len, out, out_len) == VtencErrorWrongFormat);

  return 1;
}

int test_vtenc_set_decode_u16_2(void)
{
  const uint8_t in[] = {0x03, 0x00, 0xff};
  const size_t in_len = sizeof(in);
  size_t out_len = vtenc_set_decoded_size_u16(in, in_len);
  uint16_t out[out_len];

  EXPECT_TRUE(vtenc_set_decode_u16(in, in_len, out, out_len) == VtencErrorWrongFormat);

  return 1;
}

int test_vtenc_set_decode_u16_3(void)
{
  const uint8_t in[] = {0x00, 0x00, 0x33, 0x5a};
  const size_t in_len = sizeof(in);
  const uint16_t expected_out[] = {23091};
  const size_t expected_out_len = sizeof(expected_out) / sizeof(expected_out[0]);

  return set_decode16_test(in, in_len, expected_out, expected_out_len);
}

int test_vtenc_set_decode_u16_4(void)
{
  const uint8_t in[] = {
    0x07, 0x00, 0x96, 0xae, 0x18, 0x0e, 0x10, 0x42, 0xbe, 0x53, 0x26, 0x24,
    0x7c, 0x80, 0x7e, 0x7a, 0x67
  };
  const size_t in_len = sizeof(in);
  const uint16_t expected_out[] = {1655, 3391, 4111, 8770, 29006, 32712, 32993, 58042};
  const size_t expected_out_len = sizeof(expected_out) / sizeof(expected_out[0]);

  return set_decode16_test(in, in_len, expected_out, expected_out_len);
}

int test_vtenc_set_decode_u16_5(void)
{
  const uint8_t in[] = {
    0x0b, 0x00, 0x8c, 0x24, 0x00, 0x92, 0x20, 0x09, 0x80, 0x00, 0x08, 0x08,
    0x80
  };
  const size_t in_len = sizeof(in);
  const uint16_t expected_out[] = {
    14000, 14001, 14002, 14003, 14004, 14005, 14006, 14007,
    20000, 20001, 20002, 20003
  };
  const size_t expected_out_len = sizeof(expected_out) / sizeof(expected_out[0]);

  return set_decode16_test(in, in_len, expected_out, expected_out_len);
}

int test_vtenc_set_decode_u32_1(void)
{
  const uint8_t in[] = {0x00, 0x00, 0x00, 0x00};
  const size_t in_len = sizeof(in);
  size_t out_len = 0;
  uint32_t out[out_len];

  EXPECT_TRUE(vtenc_set_decode_u32(in, in_len, out, out_len) == VtencErrorWrongFormat);

  return 1;
}

int test_vtenc_set_decode_u32_2(void)
{
  const uint8_t in[] = {0x03, 0x00, 0x00, 0x00, 0xff};
  const size_t in_len = sizeof(in);
  size_t out_len = vtenc_set_decoded_size_u32(in, in_len);
  uint32_t out[out_len];

  EXPECT_TRUE(vtenc_set_decode_u32(in, in_len, out, out_len) == VtencErrorWrongFormat);

  return 1;
}

int test_vtenc_set_decode_u32_3(void)
{
  const uint8_t in[] = {
    0x00, 0x00, 0x00, 0x00, 0x42, 0xba, 0xe3, 0x77
  };
  const size_t in_len = sizeof(in);
  const uint32_t expected_out[] = {0x77e3ba42};
  const size_t expected_out_len = sizeof(expected_out) / sizeof(expected_out[0]);

  return set_decode32_test(in, in_len, expected_out, expected_out_len);
}

int test_vtenc_set_decode_u32_4(void)
{
  const uint8_t in[] = {
    0x04, 0x00, 0x00, 0x00, 0xdc, 0x4d, 0x30, 0x20, 0xed, 0x71, 0x95, 0xf9,
    0x16, 0xde, 0xd9, 0xf1, 0x46, 0xbb, 0xfa, 0x22, 0x04, 0xb2, 0x98, 0x00
  };
  const size_t in_len = sizeof(in);
  const uint32_t expected_out[] = {
    0x98b204, 0x122fabb4, 0x378ecef0, 0x77ccab8f, 0xa40609bb
  };
  const size_t expected_out_len = sizeof(expected_out) / sizeof(expected_out[0]);

  return set_decode32_test(in, in_len, expected_out, expected_out_len);
}

int test_vtenc_set_decode_u32_5(void)
{
  const uint8_t in[] = {
    0x0d, 0x00, 0x00, 0x00, 0xee, 0xee, 0xee, 0xee, 0x06, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x88, 0x88, 0x48, 0x45, 0x40, 0x40, 0x50, 0x55,
    0x49, 0x92, 0x04, 0x41, 0x82, 0x20, 0x49, 0x12
  };
  const size_t in_len = sizeof(in);
  const uint32_t expected_out[] = {
    0xa500, 0xa501, 0xa502, 0xa503,
    0x4bbb00, 0x4bbb01,
    0xffff00, 0xffff01, 0xffff02, 0xffff03, 0xffff04, 0xffff05, 0xffff06, 0xffff07
  };
  const size_t expected_out_len = sizeof(expected_out) / sizeof(expected_out[0]);

  return set_decode32_test(in, in_len, expected_out, expected_out_len);
}

int test_vtenc_set_decode_u64_1(void)
{
  const uint8_t in[] = {0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff};
  const size_t in_len = sizeof(in);
  size_t out_len = 0;
  uint64_t out[out_len];

  EXPECT_TRUE(vtenc_set_decode_u64(in, in_len, out, out_len) == VtencErrorWrongFormat);

  return 1;
}

int test_vtenc_set_decode_u64_2(void)
{
  const uint8_t in[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
  const size_t in_len = sizeof(in);
  size_t out_len = 0;
  uint64_t out[out_len];

  EXPECT_TRUE(vtenc_set_decode_u64(in, in_len, out, out_len) == VtencErrorWrongFormat);

  return 1;
}

int test_vtenc_set_decode_u64_3(void)
{
  const uint8_t in[] = {0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfe};
  const size_t in_len = sizeof(in);
  size_t out_len = vtenc_set_decoded_size_u64(in, in_len);
  uint64_t out[out_len];

  EXPECT_TRUE(vtenc_set_decode_u64(in, in_len, out, out_len) == VtencErrorWrongFormat);

  return 1;
}

int test_vtenc_set_decode_u64_4(void)
{
  const uint8_t in[] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0xef, 0xcc, 0xaa, 0x88,
    0x66, 0x44, 0x22, 0x00
  };
  const size_t in_len = sizeof(in);
  const uint64_t expected_out[] = {0x1122334455667788ULL};
  const size_t expected_out_len = sizeof(expected_out) / sizeof(expected_out[0]);

  return set_decode64_test(in, in_len, expected_out, expected_out_len);
}

int test_vtenc_set_decode_u64_5(void)
{
  const uint8_t in[] = {
    0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfe, 0xff, 0xff, 0xff, 0xff,
    0xff, 0x9b, 0xfb, 0xbf, 0xfb, 0xbf, 0xfb, 0x4f, 0x54, 0x65, 0x76, 0x87,
    0x98, 0xb5, 0x6d, 0x5b, 0xc2, 0xc3, 0xc3, 0xc3, 0xc3, 0x57, 0x55, 0x55,
    0x55, 0x55, 0x2d, 0x04, 0x04, 0x04, 0x04, 0xa8, 0xd6, 0xcd, 0xbc, 0xab,
    0x22, 0x9a, 0x11, 0x89, 0x00
  };
  const size_t in_len = sizeof(in);
  const uint64_t expected_out[] = {
    0x11223344ULL, 0xaabbccddULL, 0x1010101010ULL, 0x5555555555ULL, 0xf0f0f0f0f0ULL,
    0x998877665544ULL, 0xffeeffeeffeeULL
  };
  const size_t expected_out_len = sizeof(expected_out) / sizeof(expected_out[0]);

  return set_decode64_test(in, in_len, expected_out, expected_out_len);
}

int test_vtenc_set_decode_u64_6(void)
{
  const uint8_t in[] = {
    0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x11, 0x11, 0x11, 0x11,
    0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x4d, 0x55, 0x55, 0x55,
    0x55, 0x55, 0x55, 0x55, 0x55, 0xd5, 0xb6, 0x4d, 0x55, 0x55, 0x55, 0x55,
    0x55, 0x55, 0x55, 0x25, 0x48, 0x92, 0x24, 0x49, 0x92, 0x24, 0x49, 0x92,
    0x24, 0x49, 0x02
  };
  const size_t in_len = sizeof(in);
  const uint64_t expected_out[] = {
    0x20000000ULL, 0x20000001ULL, 0x20000002ULL, 0x20000003ULL,
    0x80000000ULL, 0x80000001ULL,
    0x2000000000ULL, 0x2000000001ULL
  };
  const size_t expected_out_len = sizeof(expected_out) / sizeof(expected_out[0]);

  return set_decode64_test(in, in_len, expected_out, expected_out_len);
}

int test_vtenc_list_decoded_size_1(void)
{
  const uint8_t in[] = {};
  const size_t in_len = sizeof(in);

  EXPECT_TRUE(vtenc_list_decoded_size_u8(in, in_len) == 0);
  EXPECT_TRUE(vtenc_list_decoded_size_u16(in, in_len) == 0);
  EXPECT_TRUE(vtenc_list_decoded_size_u32(in, in_len) == 0);
  EXPECT_TRUE(vtenc_list_decoded_size_u64(in, in_len) == 0);

  return 1;
}

int test_vtenc_list_decoded_size_2(void)
{
  const uint8_t in[] = {0xff, 0xff};
  const size_t in_len = sizeof(in);

  EXPECT_TRUE(vtenc_list_decoded_size_u8(in, in_len) == 0);
  EXPECT_TRUE(vtenc_list_decoded_size_u16(in, in_len) == 0);
  EXPECT_TRUE(vtenc_list_decoded_size_u32(in, in_len) == 0);
  EXPECT_TRUE(vtenc_list_decoded_size_u64(in, in_len) == 0);

  return 1;
}

int test_vtenc_list_decoded_size_3(void)
{
  const uint8_t in[] = {0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
  const size_t in_len = sizeof(in);

  EXPECT_TRUE(vtenc_list_decoded_size_u8(in, in_len) == 7);
  EXPECT_TRUE(vtenc_list_decoded_size_u16(in, in_len) == 7);
  EXPECT_TRUE(vtenc_list_decoded_size_u32(in, in_len) == 7);
  EXPECT_TRUE(vtenc_list_decoded_size_u64(in, in_len) == 7);

  return 1;
}

int test_vtenc_list_decoded_size_4(void)
{
  const uint8_t in[] = {0xff, 0xff, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x00};
  const size_t in_len = sizeof(in);

  EXPECT_TRUE(vtenc_list_decoded_size_u8(in, in_len) == 1048575);
  EXPECT_TRUE(vtenc_list_decoded_size_u16(in, in_len) == 1048575);
  EXPECT_TRUE(vtenc_list_decoded_size_u32(in, in_len) == 1048575);
  EXPECT_TRUE(vtenc_list_decoded_size_u64(in, in_len) == 1048575);

  return 1;
}

int test_vtenc_set_decoded_size_with_wrong_input(void)
{
  const uint8_t in[] = {};
  const size_t in_len = sizeof(in);

  EXPECT_TRUE(vtenc_set_decoded_size_u8(in, in_len) == 0);
  EXPECT_TRUE(vtenc_set_decoded_size_u16(in, in_len) == 0);
  EXPECT_TRUE(vtenc_set_decoded_size_u32(in, in_len) == 0);
  EXPECT_TRUE(vtenc_set_decoded_size_u64(in, in_len) == 0);

  return 1;
}

int test_vtenc_set_decoded_size_u8(void)
{
  const uint8_t *in;
  const size_t in_len = 1;

  in = (const uint8_t *)"\x00"; EXPECT_TRUE(vtenc_set_decoded_size_u8(in, in_len) == 1);
  in = (const uint8_t *)"\x05"; EXPECT_TRUE(vtenc_set_decoded_size_u8(in, in_len) == 6);
  in = (const uint8_t *)"\x34"; EXPECT_TRUE(vtenc_set_decoded_size_u8(in, in_len) == 53);
  in = (const uint8_t *)"\xb3"; EXPECT_TRUE(vtenc_set_decoded_size_u8(in, in_len) == 180);
  in = (const uint8_t *)"\xff"; EXPECT_TRUE(vtenc_set_decoded_size_u8(in, in_len) == 256);

  return 1;
}

int test_vtenc_set_decoded_size_u16(void)
{
  const uint8_t *in;
  const size_t in_len = 2;

  in = (const uint8_t *)"\x00\x00"; EXPECT_TRUE(vtenc_set_decoded_size_u16(in, in_len) == 1);
  in = (const uint8_t *)"\x01\x01"; EXPECT_TRUE(vtenc_set_decoded_size_u16(in, in_len) == 258);
  in = (const uint8_t *)"\x25\x33"; EXPECT_TRUE(vtenc_set_decoded_size_u16(in, in_len) == 13094);
  in = (const uint8_t *)"\x00\xff"; EXPECT_TRUE(vtenc_set_decoded_size_u16(in, in_len) == 65281);
  in = (const uint8_t *)"\xff\xff"; EXPECT_TRUE(vtenc_set_decoded_size_u16(in, in_len) == 65536);

  return 1;
}

int test_vtenc_set_decoded_size_u32(void)
{
  const uint8_t *in;
  const size_t in_len = 4;

  in = (const uint8_t *)"\x00\x00\x00\x00"; EXPECT_TRUE(vtenc_set_decoded_size_u32(in, in_len) == 1);
  in = (const uint8_t *)"\x01\x01\x01\x01"; EXPECT_TRUE(vtenc_set_decoded_size_u32(in, in_len) == 16843010);
  in = (const uint8_t *)"\x55\x55\x55\x55"; EXPECT_TRUE(vtenc_set_decoded_size_u32(in, in_len) == 1431655766);
  in = (const uint8_t *)"\x00\xff\xff\x00"; EXPECT_TRUE(vtenc_set_decoded_size_u32(in, in_len) == 16776961);
  in = (const uint8_t *)"\xff\xff\xff\xff"; EXPECT_TRUE(vtenc_set_decoded_size_u32(in, in_len) == 4294967296);

  return 1;
}

int test_vtenc_set_decoded_size_u64(void)
{
  const uint8_t *in;
  const size_t in_len = 8;

  in = (const uint8_t *)"\x00\x00\x00\x00\x00\x00\x00\x00"; EXPECT_TRUE(vtenc_set_decoded_size_u64(in, in_len) == 1);
  in = (const uint8_t *)"\x01\x01\x01\x01\x01\x01\x01\x01"; EXPECT_TRUE(vtenc_set_decoded_size_u64(in, in_len) == 0x0101010101010102ULL);
  in = (const uint8_t *)"\x55\x55\x55\x55\x55\x55\x55\x55"; EXPECT_TRUE(vtenc_set_decoded_size_u64(in, in_len) == 0x0155555555555556ULL);
  in = (const uint8_t *)"\x00\xff\xff\x00\x00\xff\xff\x00"; EXPECT_TRUE(vtenc_set_decoded_size_u64(in, in_len) == 0x00ffff0000ffff01ULL);
  in = (const uint8_t *)"\xff\xff\xff\xff\xff\xff\xff\xff"; EXPECT_TRUE(vtenc_set_decoded_size_u64(in, in_len) == 0x0200000000000000ULL);

  return 1;
}
