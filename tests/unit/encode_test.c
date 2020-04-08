/**
  Copyright (c) 2019 Vicente Romero Calero. All rights reserved.
  Licensed under the MIT License.
  See LICENSE file in the project root for full license information.
 */
#include <stdlib.h>
#include <string.h>

#include "unit_tests.h"
#include "../../vtenc.h"

int list_encode8_test(const uint8_t *in, size_t in_len,
  const uint8_t *expected_out, size_t expected_out_len)
{
  const size_t out_cap = vtenc_list_max_encoded_size_u8(in_len);
  uint8_t out[out_cap];
  size_t out_len;

  EXPECT_TRUE(vtenc_list_encode_u8(in, in_len, out, out_cap, &out_len) == VtencErrorNoError);
  EXPECT_TRUE(out_len == expected_out_len);
  EXPECT_TRUE(memcmp(out, expected_out, expected_out_len) == 0);

  return 1;
}

int list_encode16_test(const uint16_t *in, size_t in_len,
  const uint8_t *expected_out, size_t expected_out_len)
{
  const size_t out_cap = vtenc_list_max_encoded_size_u16(in_len);
  uint8_t out[out_cap];
  size_t out_len;

  EXPECT_TRUE(vtenc_list_encode_u16(in, in_len, out, out_cap, &out_len) == VtencErrorNoError);
  EXPECT_TRUE(out_len == expected_out_len);
  EXPECT_TRUE(memcmp(out, expected_out, expected_out_len) == 0);

  return 1;
}

int list_encode32_test(const uint32_t *in, size_t in_len,
  const uint8_t *expected_out, size_t expected_out_len)
{
  const size_t out_cap = vtenc_list_max_encoded_size_u32(in_len);
  uint8_t out[out_cap];
  size_t out_len;

  EXPECT_TRUE(vtenc_list_encode_u32(in, in_len, out, out_cap, &out_len) == VtencErrorNoError);
  EXPECT_TRUE(out_len == expected_out_len);
  EXPECT_TRUE(memcmp(out, expected_out, expected_out_len) == 0);

  return 1;
}

int list_encode64_test(const uint64_t *in, size_t in_len,
  const uint8_t *expected_out, size_t expected_out_len)
{
  const size_t out_cap = vtenc_list_max_encoded_size_u64(in_len);
  uint8_t out[out_cap];
  size_t out_len;

  EXPECT_TRUE(vtenc_list_encode_u64(in, in_len, out, out_cap, &out_len) == VtencErrorNoError);
  EXPECT_TRUE(out_len == expected_out_len);
  EXPECT_TRUE(memcmp(out, expected_out, expected_out_len) == 0);

  return 1;
}

int set_encode8_test(const uint8_t *in, size_t in_len,
  const uint8_t *expected_out, size_t expected_out_len)
{
  const size_t out_cap = vtenc_set_max_encoded_size_u8(in_len);
  uint8_t out[out_cap];
  size_t out_len;

  EXPECT_TRUE(vtenc_set_encode_u8(in, in_len, out, out_cap, &out_len) == VtencErrorNoError);
  EXPECT_TRUE(out_len == expected_out_len);
  EXPECT_TRUE(memcmp(out, expected_out, expected_out_len) == 0);

  return 1;
}

int set_encode16_test(const uint16_t *in, size_t in_len,
  const uint8_t *expected_out, size_t expected_out_len)
{
  const size_t out_cap = vtenc_set_max_encoded_size_u16(in_len);
  uint8_t out[out_cap];
  size_t out_len;

  EXPECT_TRUE(vtenc_set_encode_u16(in, in_len, out, out_cap, &out_len) == VtencErrorNoError);
  EXPECT_TRUE(out_len == expected_out_len);
  EXPECT_TRUE(memcmp(out, expected_out, expected_out_len) == 0);

  return 1;
}

int set_encode32_test(const uint32_t *in, size_t in_len,
  const uint8_t *expected_out, size_t expected_out_len)
{
  const size_t out_cap = vtenc_set_max_encoded_size_u32(in_len);
  uint8_t out[out_cap];
  size_t out_len;

  EXPECT_TRUE(vtenc_set_encode_u32(in, in_len, out, out_cap, &out_len) == VtencErrorNoError);
  EXPECT_TRUE(out_len == expected_out_len);
  EXPECT_TRUE(memcmp(out, expected_out, expected_out_len) == 0);

  return 1;
}

int set_encode64_test(const uint64_t *in, size_t in_len,
  const uint8_t *expected_out, size_t expected_out_len)
{
  const size_t out_cap = vtenc_set_max_encoded_size_u64(in_len);
  uint8_t out[out_cap];
  size_t out_len;

  EXPECT_TRUE(vtenc_set_encode_u64(in, in_len, out, out_cap, &out_len) == VtencErrorNoError);
  EXPECT_TRUE(out_len == expected_out_len);
  EXPECT_TRUE(memcmp(out, expected_out, expected_out_len) == 0);

  return 1;
}

int test_vtenc_list_encode_u8_1(void)
{
  const uint8_t in[] = {};
  const size_t in_len = sizeof(in);
  const uint8_t expected_out[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
  const size_t expected_out_len = sizeof(expected_out);

  return list_encode8_test(in, in_len, expected_out, expected_out_len);
}

int test_vtenc_list_encode_u8_2(void)
{
  const uint8_t in[] = {38};
  const size_t in_len = sizeof(in);
  const uint8_t expected_out[] = {0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x4c, 0x00};
  const size_t expected_out_len = sizeof(expected_out);

  return list_encode8_test(in, in_len, expected_out, expected_out_len);
}

int test_vtenc_list_encode_u8_3(void)
{
  const uint8_t in[] = {5, 22, 23, 44, 62, 69, 109, 113, 178, 194, 206};
  const size_t in_len = sizeof(in);
  const uint8_t expected_out[] = {
    0x0b, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 0xcd, 0x92, 0xab, 0xa2,
    0xcb, 0x72, 0x4e, 0xa8, 0x00
  };
  const size_t expected_out_len = sizeof(expected_out);

  return list_encode8_test(in, in_len, expected_out, expected_out_len);
}

int test_vtenc_list_encode_u8_4(void)
{
  const uint8_t in[] = {57, 57, 57, 111, 111, 111, 111, 208, 208};
  const size_t in_len = sizeof(in);
  const uint8_t expected_out[] = {
    0x09, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0e, 0x51, 0x1d, 0x08, 0x00,
    0xc0, 0x03
  };
  const size_t expected_out_len = sizeof(expected_out);

  return list_encode8_test(in, in_len, expected_out, expected_out_len);
}

int test_vtenc_list_encode_u16_1(void)
{
  const uint16_t in[] = {};
  const size_t in_len = 0;
  const uint8_t expected_out[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
  const size_t expected_out_len = sizeof(expected_out);

  return list_encode16_test(in, in_len, expected_out, expected_out_len);
}

int test_vtenc_list_encode_u16_2(void)
{
  const uint16_t in[] = {13862};
  const size_t in_len = sizeof(in) / sizeof(in[0]);
  const uint8_t expected_out[] = {
    0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x4c, 0x6c, 0x00
  };
  const size_t expected_out_len = sizeof(expected_out);

  return list_encode16_test(in, in_len, expected_out, expected_out_len);
}

int test_vtenc_list_encode_u16_3(void)
{
  const uint16_t in[] = {1099, 2227, 8102, 27654, 29001, 35511, 50083};
  const size_t in_len = sizeof(in) / sizeof(in[0]);
  const uint8_t expected_out[] = {
    0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xda, 0xe8, 0x70, 0xab, 0x8c,
    0x92, 0xc2, 0x80, 0xd7, 0xf4, 0x9b, 0xc5, 0x12, 0x01
  };
  const size_t expected_out_len = sizeof(expected_out);

  return list_encode16_test(in, in_len, expected_out, expected_out_len);
}

int test_vtenc_list_encode_u16_4(void)
{
  const uint16_t in[] = {677, 677, 677, 8881, 8881, 8881, 8881, 8881};
  const size_t in_len = sizeof(in) / sizeof(in[0]);
  const uint8_t expected_out[] = {
    0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0xa7, 0x2d, 0x8a, 0x02,
    0x6d, 0xf1, 0x33, 0xf3, 0x0c
  };
  const size_t expected_out_len = sizeof(expected_out);

  return list_encode16_test(in, in_len, expected_out, expected_out_len);
}

int test_vtenc_list_encode_u32_1(void)
{
  const uint32_t in[] = {};
  const size_t in_len = 0;
  const uint8_t expected_out[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
  const size_t expected_out_len = sizeof(expected_out);

  return list_encode32_test(in, in_len, expected_out, expected_out_len);
}

int test_vtenc_list_encode_u32_2(void)
{
  const uint32_t in[] = {726550617};
  const size_t in_len = sizeof(in) / sizeof(in[0]);
  const uint8_t expected_out[] = {
    0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xb2, 0x90, 0x9c, 0x56, 0x00
  };
  const size_t expected_out_len = sizeof(expected_out);

  return list_encode32_test(in, in_len, expected_out, expected_out_len);
}

int test_vtenc_list_encode_u32_3(void)
{
  const uint32_t in[] = {5348, 13089333, 88199704, 271008013, 1451881090};
  const size_t in_len = sizeof(in) / sizeof(in[0]);
  const uint8_t expected_out[] = {
    0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x4a, 0x41, 0xf9, 0x44, 0x8b,
    0x6b, 0x08, 0x3a, 0x81, 0xc5, 0x90, 0x0e, 0x4a, 0xab, 0xd1, 0x3d, 0x92,
    0x53, 0x00, 0x00
  };
  const size_t expected_out_len = sizeof(expected_out);

  return list_encode32_test(in, in_len, expected_out, expected_out_len);
}

int test_vtenc_list_encode_u32_4(void)
{
  const uint32_t in[] = {77865901, 77865901, 77865901, 77865901, 314976310, 314976310};
  const size_t in_len = sizeof(in) / sizeof(in[0]);
  const uint8_t expected_out[] = {
    0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x6c, 0x53, 0x11, 0x54, 0x50,
    0x11, 0x55, 0x41, 0x90, 0x20, 0x41, 0x90, 0x20, 0x49, 0x90, 0x04, 0x40,
    0x10, 0x20, 0x00
  };
  const size_t expected_out_len = sizeof(expected_out);

  return list_encode32_test(in, in_len, expected_out, expected_out_len);
}

int test_vtenc_list_encode_u64_1(void)
{
  const uint64_t in[] = {};
  const size_t in_len = 0;
  const uint8_t expected_out[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
  const size_t expected_out_len = sizeof(expected_out);

  return list_encode64_test(in, in_len, expected_out, expected_out_len);
}

int test_vtenc_list_encode_u64_2(void)
{
  const uint64_t in[] = {0xab778190fec42261ULL};
  const size_t in_len = sizeof(in) / sizeof(in[0]);
  const uint8_t expected_out[] = {
    0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc2, 0x44, 0x88, 0xfd, 0x21,
    0x03, 0xef, 0x56, 0x01
  };
  const size_t expected_out_len = sizeof(expected_out);

  return list_encode64_test(in, in_len, expected_out, expected_out_len);
}

int test_vtenc_list_encode_u64_3(void)
{
  const uint64_t in[] = {0x12a6ULL, 0x8addf0ULL, 0xffa1b4bbULL, 0x21258ee39aaaULL};
  const size_t in_len = sizeof(in) / sizeof(in[0]);
  const uint8_t expected_out[] = {
    0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x48, 0x92, 0x24, 0x49, 0x92,
    0x24, 0xc9, 0xa9, 0x6a, 0x8e, 0x3b, 0x96, 0x84, 0xff, 0xff, 0xff, 0xdd,
    0xa5, 0x0d, 0xfd, 0xab, 0xaa, 0xc1, 0x77, 0x2b, 0x4c, 0x25, 0x00
  };
  const size_t expected_out_len = sizeof(expected_out);

  return list_encode64_test(in, in_len, expected_out, expected_out_len);
}

int test_vtenc_list_encode_u64_4(void)
{
  const uint64_t in[] = {
    0x55555555ULL, 0x55555555ULL, 0x55555555ULL, 0x111111111111ULL, 0x111111111111ULL
  };
  const size_t in_len = sizeof(in) / sizeof(in[0]);
  const uint8_t expected_out[] = {
    0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xda, 0xb6, 0x6d, 0xdb, 0xb6,
    0x6d, 0xdb, 0x4e, 0x45, 0x45, 0x45, 0x45, 0x45, 0x45, 0x45, 0x45, 0x45,
    0x45, 0xe5, 0xff, 0xff, 0x7f, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66,
    0x06
  };
  const size_t expected_out_len = sizeof(expected_out);

  return list_encode64_test(in, in_len, expected_out, expected_out_len);
}

int test_vtenc_set_encode_u8_1(void)
{
  const uint8_t in[] = {};
  const size_t in_len = 0;
  const size_t out_cap = 0;
  uint8_t out[out_cap];
  size_t out_len;

  EXPECT_TRUE(vtenc_set_encode_u8(in, in_len, out, out_cap, &out_len) == VtencErrorInputTooSmall);

  return 1;
}

int test_vtenc_set_encode_u8_2(void)
{
  const uint8_t in[] = {};
  const size_t in_len = 257;
  const size_t out_cap = 0;
  uint8_t out[out_cap];
  size_t out_len;

  EXPECT_TRUE(vtenc_set_encode_u8(in, in_len, out, out_cap, &out_len) == VtencErrorInputTooBig);

  return 1;
}

int test_vtenc_set_encode_u8_3(void)
{
  const size_t in_len = 256;
  uint8_t in[in_len];
  const uint8_t expected_out[] = {0xff};
  const size_t expected_out_len = sizeof(expected_out);
  size_t i;

  for (i=0; i<in_len; ++i) in[i] = (uint8_t)i;

  return set_encode8_test(in, in_len, expected_out, expected_out_len);
}

int test_vtenc_set_encode_u8_4(void)
{
  const uint8_t in[] = {33};
  const size_t in_len = sizeof(in);
  const uint8_t expected_out[] = {0x00, 0x21};
  const size_t expected_out_len = sizeof(expected_out);

  return set_encode8_test(in, in_len, expected_out, expected_out_len);
}

int test_vtenc_set_encode_u8_5(void)
{
  const uint8_t in[] = {0, 1, 2, 3, 4, 5, 6, 7, 160, 161, 162, 163};
  const size_t in_len = sizeof(in);
  const uint8_t expected_out[] = {0x0b, 0x48, 0x90, 0x44, 0x44, 0x04};
  const size_t expected_out_len = sizeof(expected_out);

  return set_encode8_test(in, in_len, expected_out, expected_out_len);
}

int test_vtenc_set_encode_u8_6(void)
{
  const uint8_t in[] = {13, 77, 88, 93, 149, 212};
  const size_t in_len = sizeof(in);
  const uint8_t expected_out[] = {0x05, 0x8c, 0xaa, 0x72, 0x14, 0xdd, 0x00};
  const size_t expected_out_len = sizeof(expected_out);

  return set_encode8_test(in, in_len, expected_out, expected_out_len);
}

int test_vtenc_set_encode_u16_1(void)
{
  const uint16_t in[] = {};
  const size_t in_len = 0;
  const size_t out_cap = 0;
  uint8_t out[out_cap];
  size_t out_len;

  EXPECT_TRUE(vtenc_set_encode_u16(in, in_len, out, out_cap, &out_len) == VtencErrorInputTooSmall);

  return 1;
}

int test_vtenc_set_encode_u16_2(void)
{
  const uint16_t in[] = {};
  const size_t in_len = 65537;
  const size_t out_cap = 0;
  uint8_t out[out_cap];
  size_t out_len;

  EXPECT_TRUE(vtenc_set_encode_u16(in, in_len, out, out_cap, &out_len) == VtencErrorInputTooBig);

  return 1;
}

int test_vtenc_set_encode_u16_3(void)
{
  const uint16_t in[] = {23091};
  const size_t in_len = sizeof(in) / sizeof(in[0]);
  const uint8_t expected_out[] = {0x00, 0x00, 0x33, 0x5a};
  const size_t expected_out_len = sizeof(expected_out);

  return set_encode16_test(in, in_len, expected_out, expected_out_len);
}

int test_vtenc_set_encode_u16_4(void)
{
  const uint16_t in[] = {1655, 3391, 4111, 8770, 29006, 32712, 32993, 58042};
  const size_t in_len = sizeof(in) / sizeof(in[0]);
  const uint8_t expected_out[] = {
    0x07, 0x00, 0x96, 0xae, 0x18, 0x0e, 0x10, 0x42, 0xbe, 0x53, 0x26, 0x24,
    0x7c, 0x80, 0x7e, 0x7a, 0x67
  };
  const size_t expected_out_len = sizeof(expected_out);

  return set_encode16_test(in, in_len, expected_out, expected_out_len);
}

int test_vtenc_set_encode_u16_5(void)
{
  const uint16_t in[] = {
    14000, 14001, 14002, 14003, 14004, 14005, 14006, 14007,
    20000, 20001, 20002, 20003
  };
  const size_t in_len = sizeof(in) / sizeof(in[0]);
  const uint8_t expected_out[] = {
    0x0b, 0x00, 0x8c, 0x24, 0x00, 0x92, 0x20, 0x09, 0x80, 0x00, 0x08, 0x08,
    0x80
  };
  const size_t expected_out_len = sizeof(expected_out);

  return set_encode16_test(in, in_len, expected_out, expected_out_len);
}

int test_vtenc_set_encode_u32_1(void)
{
  const uint32_t in[] = {};
  const size_t in_len = 0;
  const size_t out_cap = 0;
  uint8_t out[out_cap];
  size_t out_len;

  EXPECT_TRUE(vtenc_set_encode_u32(in, in_len, out, out_cap, &out_len) == VtencErrorInputTooSmall);

  return 1;
}

int test_vtenc_set_encode_u32_2(void)
{
  const uint32_t in[] = {};
  const size_t in_len = 0x200000000;
  const size_t out_cap = 0;
  uint8_t out[out_cap];
  size_t out_len;

  EXPECT_TRUE(vtenc_set_encode_u32(in, in_len, out, out_cap, &out_len) == VtencErrorInputTooBig);

  return 1;
}

int test_vtenc_set_encode_u32_3(void)
{
  const uint32_t in[] = {0x77e3ba42};
  const size_t in_len = sizeof(in) / sizeof(in[0]);
  const uint8_t expected_out[] = {
    0x00, 0x00, 0x00, 0x00, 0x42, 0xba, 0xe3, 0x77
  };
  const size_t expected_out_len = sizeof(expected_out);

  return set_encode32_test(in, in_len, expected_out, expected_out_len);
}

int test_vtenc_set_encode_u32_4(void)
{
  const uint32_t in[] = {0x98b204, 0x122fabb4, 0x378ecef0, 0x77ccab8f, 0xa40609bb};
  const size_t in_len = sizeof(in) / sizeof(in[0]);
  const uint8_t expected_out[] = {
    0x04, 0x00, 0x00, 0x00, 0xdc, 0x4d, 0x30, 0x20, 0xed, 0x71, 0x95, 0xf9,
    0x16, 0xde, 0xd9, 0xf1, 0x46, 0xbb, 0xfa, 0x22, 0x04, 0xb2, 0x98, 0x00
  };
  const size_t expected_out_len = sizeof(expected_out);

  return set_encode32_test(in, in_len, expected_out, expected_out_len);
}

int test_vtenc_set_encode_u32_5(void)
{
  const uint32_t in[] = {
    0xa500, 0xa501, 0xa502, 0xa503,
    0x4bbb00, 0x4bbb01,
    0xffff00, 0xffff01, 0xffff02, 0xffff03, 0xffff04, 0xffff05, 0xffff06, 0xffff07
  };
  const size_t in_len = sizeof(in) / sizeof(in[0]);
  const uint8_t expected_out[] = {
    0x0d, 0x00, 0x00, 0x00, 0xee, 0xee, 0xee, 0xee, 0x06, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x88, 0x88, 0x48, 0x45, 0x40, 0x40, 0x50, 0x55,
    0x49, 0x92, 0x04, 0x41, 0x82, 0x20, 0x49, 0x12
  };
  const size_t expected_out_len = sizeof(expected_out);

  return set_encode32_test(in, in_len, expected_out, expected_out_len);
}

int test_vtenc_set_encode_u64_1(void)
{
  const uint64_t in[] = {};
  const size_t in_len = 0;
  const size_t out_cap = 0;
  uint8_t out[out_cap];
  size_t out_len;

  EXPECT_TRUE(vtenc_set_encode_u64(in, in_len, out, out_cap, &out_len) == VtencErrorInputTooSmall);

  return 1;
}

int test_vtenc_set_encode_u64_2(void)
{
  const uint64_t in[] = {0x1122334455667788ULL};
  const size_t in_len = sizeof(in) / sizeof(in[0]);
  const uint8_t expected_out[] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0xef, 0xcc, 0xaa, 0x88,
    0x66, 0x44, 0x22, 0x00
  };
  const size_t expected_out_len = sizeof(expected_out);

  return set_encode64_test(in, in_len, expected_out, expected_out_len);
}

int test_vtenc_set_encode_u64_3(void)
{
  const uint64_t in[] = {
    0x11223344ULL, 0xaabbccddULL, 0x1010101010ULL, 0x5555555555ULL, 0xf0f0f0f0f0ULL,
    0x998877665544ULL, 0xffeeffeeffeeULL
  };
  const size_t in_len = sizeof(in) / sizeof(in[0]);
  const uint8_t expected_out[] = {
    0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfe, 0xff, 0xff, 0xff, 0xff,
    0xff, 0x9b, 0xfb, 0xbf, 0xfb, 0xbf, 0xfb, 0x4f, 0x54, 0x65, 0x76, 0x87,
    0x98, 0xb5, 0x6d, 0x5b, 0xc2, 0xc3, 0xc3, 0xc3, 0xc3, 0x57, 0x55, 0x55,
    0x55, 0x55, 0x2d, 0x04, 0x04, 0x04, 0x04, 0xa8, 0xd6, 0xcd, 0xbc, 0xab,
    0x22, 0x9a, 0x11, 0x89, 0x00
  };
  const size_t expected_out_len = sizeof(expected_out);

  return set_encode64_test(in, in_len, expected_out, expected_out_len);
}

int test_vtenc_set_encode_u64_4(void)
{
  const uint64_t in[] = {
    0x20000000ULL, 0x20000001ULL, 0x20000002ULL, 0x20000003ULL,
    0x80000000ULL, 0x80000001ULL,
    0x2000000000ULL, 0x2000000001ULL
  };
  const size_t in_len = sizeof(in) / sizeof(in[0]);
  const uint8_t expected_out[] = {
    0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x11, 0x11, 0x11, 0x11,
    0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x4d, 0x55, 0x55, 0x55,
    0x55, 0x55, 0x55, 0x55, 0x55, 0xd5, 0xb6, 0x4d, 0x55, 0x55, 0x55, 0x55,
    0x55, 0x55, 0x55, 0x25, 0x48, 0x92, 0x24, 0x49, 0x92, 0x24, 0x49, 0x92,
    0x24, 0x49, 0x02
  };
  const size_t expected_out_len = sizeof(expected_out);

  return set_encode64_test(in, in_len, expected_out, expected_out_len);
}

int test_vtenc_list_max_encoded_size_u8(void)
{
  EXPECT_TRUE(vtenc_list_max_encoded_size_u8(0) == 8);
  EXPECT_TRUE(vtenc_list_max_encoded_size_u8(1) == 16);
  EXPECT_TRUE(vtenc_list_max_encoded_size_u8(5) == 16);
  EXPECT_TRUE(vtenc_list_max_encoded_size_u8(10) == 24);
  EXPECT_TRUE(vtenc_list_max_encoded_size_u8(100) == 112);
  EXPECT_TRUE(vtenc_list_max_encoded_size_u8(1000) == 1008);

  return 1;
}

int test_vtenc_list_max_encoded_size_u16(void)
{
  EXPECT_TRUE(vtenc_list_max_encoded_size_u16(0) == 16);
  EXPECT_TRUE(vtenc_list_max_encoded_size_u16(1) == 16);
  EXPECT_TRUE(vtenc_list_max_encoded_size_u16(5) == 24);
  EXPECT_TRUE(vtenc_list_max_encoded_size_u16(10) == 32);
  EXPECT_TRUE(vtenc_list_max_encoded_size_u16(100) == 216);
  EXPECT_TRUE(vtenc_list_max_encoded_size_u16(1000) == 2016);

  return 1;
}

int test_vtenc_list_max_encoded_size_u32(void)
{
  EXPECT_TRUE(vtenc_list_max_encoded_size_u32(0) == 16);
  EXPECT_TRUE(vtenc_list_max_encoded_size_u32(1) == 16);
  EXPECT_TRUE(vtenc_list_max_encoded_size_u32(5) == 32);
  EXPECT_TRUE(vtenc_list_max_encoded_size_u32(10) == 56);
  EXPECT_TRUE(vtenc_list_max_encoded_size_u32(100) == 416);
  EXPECT_TRUE(vtenc_list_max_encoded_size_u32(1000) == 4016);

  return 1;
}

int test_vtenc_list_max_encoded_size_u64(void)
{
  EXPECT_TRUE(vtenc_list_max_encoded_size_u64(0) == 16);
  EXPECT_TRUE(vtenc_list_max_encoded_size_u64(1) == 24);
  EXPECT_TRUE(vtenc_list_max_encoded_size_u64(5) == 56);
  EXPECT_TRUE(vtenc_list_max_encoded_size_u64(10) == 96);
  EXPECT_TRUE(vtenc_list_max_encoded_size_u64(100) == 816);
  EXPECT_TRUE(vtenc_list_max_encoded_size_u64(1000) == 8016);

  return 1;
}

int test_vtenc_set_max_encoded_size_u8(void)
{
  EXPECT_TRUE(vtenc_set_max_encoded_size_u8(0) == 8);
  EXPECT_TRUE(vtenc_set_max_encoded_size_u8(1) == 8);
  EXPECT_TRUE(vtenc_set_max_encoded_size_u8(5) == 8);
  EXPECT_TRUE(vtenc_set_max_encoded_size_u8(10) == 16);
  EXPECT_TRUE(vtenc_set_max_encoded_size_u8(100) == 104);

  return 1;
}

int test_vtenc_set_max_encoded_size_u16(void)
{
  EXPECT_TRUE(vtenc_set_max_encoded_size_u16(0) == 8);
  EXPECT_TRUE(vtenc_set_max_encoded_size_u16(1) == 8);
  EXPECT_TRUE(vtenc_set_max_encoded_size_u16(5) == 16);
  EXPECT_TRUE(vtenc_set_max_encoded_size_u16(10) == 24);
  EXPECT_TRUE(vtenc_set_max_encoded_size_u16(100) == 208);
  EXPECT_TRUE(vtenc_set_max_encoded_size_u16(1000) == 2008);

  return 1;
}

int test_vtenc_set_max_encoded_size_u32(void)
{
  EXPECT_TRUE(vtenc_set_max_encoded_size_u32(0) == 8);
  EXPECT_TRUE(vtenc_set_max_encoded_size_u32(1) == 16);
  EXPECT_TRUE(vtenc_set_max_encoded_size_u32(5) == 32);
  EXPECT_TRUE(vtenc_set_max_encoded_size_u32(10) == 48);
  EXPECT_TRUE(vtenc_set_max_encoded_size_u32(100) == 408);
  EXPECT_TRUE(vtenc_set_max_encoded_size_u32(1000) == 4008);

  return 1;
}

int test_vtenc_set_max_encoded_size_u64(void)
{
  EXPECT_TRUE(vtenc_set_max_encoded_size_u64(0) == 16);
  EXPECT_TRUE(vtenc_set_max_encoded_size_u64(1) == 24);
  EXPECT_TRUE(vtenc_set_max_encoded_size_u64(5) == 56);
  EXPECT_TRUE(vtenc_set_max_encoded_size_u64(10) == 96);
  EXPECT_TRUE(vtenc_set_max_encoded_size_u64(100) == 816);
  EXPECT_TRUE(vtenc_set_max_encoded_size_u64(1000) == 8016);

  return 1;
}

int test_vtenc_encoder_init(void)
{
  VtencEncoder enc;

  vtenc_encoder_init(&enc);

  EXPECT_TRUE(enc.has_repeated_values == 1);
  EXPECT_TRUE(enc.skip_full_subtrees == 0);
  EXPECT_TRUE(enc.last_error_code == VtencErrorNoError);

  return 1;
}

struct EncodeTestCaseInput {
  VtencEncoder encoder;
  const void *values;
  size_t values_len;
};

struct EncodeTestCaseOutput {
  uint8_t *bytes;
  size_t bytes_len;
  VtencErrorCode last_error_code;
};

struct EncodeTestCase {
  struct EncodeTestCaseInput input;
  struct EncodeTestCaseOutput expected_output;
};

static struct EncodeTestCase test_cases8[] = {
  {
    .input = {
      .encoder = {
        .has_repeated_values = 1,
        .skip_full_subtrees = 0
      },
      .values = (uint8_t []){},
      .values_len = 0
    },
    .expected_output = {
      .bytes = (uint8_t []){0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
      .bytes_len = 8,
      .last_error_code = VtencErrorNoError
    }
  },
  {
    .input = {
      .encoder = {
        .has_repeated_values = 1,
        .skip_full_subtrees = 0
      },
      .values = (uint8_t []){38},
      .values_len = 1
    },
    .expected_output = {
      .bytes = (uint8_t []){0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x4c, 0x00},
      .bytes_len = 9,
      .last_error_code = VtencErrorNoError
    }
  },
  {
    .input = {
      .encoder = {
        .has_repeated_values = 1,
        .skip_full_subtrees = 0
      },
      .values = (uint8_t []){5, 22, 23, 44, 62, 69, 109, 113, 178, 194, 206},
      .values_len = 11
    },
    .expected_output = {
      .bytes = (uint8_t []){
        0x0b, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 0xcd, 0x92, 0xab, 0xa2,
        0xcb, 0x72, 0x4e, 0xa8, 0x00
      },
      .bytes_len = 17,
      .last_error_code = VtencErrorNoError
    }
  },
  {
    .input = {
      .encoder = {
        .has_repeated_values = 1,
        .skip_full_subtrees = 0
      },
      .values = (uint8_t []){57, 57, 57, 111, 111, 111, 111, 208, 208},
      .values_len = 9
    },
    .expected_output = {
      .bytes = (uint8_t []){
        0x09, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0e, 0x51, 0x1d, 0x08, 0x00,
        0xc0, 0x03
      },
      .bytes_len = 14,
      .last_error_code = VtencErrorNoError
    }
  },
  {
    .input = {
      .encoder = {
        .has_repeated_values = 0,
        .skip_full_subtrees = 1
      },
      .values = (uint8_t []){},
      .values_len = 0
    },
    .expected_output = {
      .bytes = (uint8_t []){},
      .bytes_len = 0,
      .last_error_code = VtencErrorInputTooSmall
    }
  },
  {
    .input = {
      .encoder = {
        .has_repeated_values = 0,
        .skip_full_subtrees = 1
      },
      .values = (uint8_t []){},
      .values_len = 257
    },
    .expected_output = {
      .bytes = (uint8_t []){},
      .bytes_len = 0,
      .last_error_code = VtencErrorInputTooBig
    }
  },
  {
    .input = {
      .encoder = {
        .has_repeated_values = 0,
        .skip_full_subtrees = 1
      },
      .values = (uint8_t []){
        0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19,
        20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37,
        38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55,
        56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73,
        74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 91,
        92, 93, 94, 95, 96, 97, 98, 99, 100, 101, 102, 103, 104, 105, 106, 107,
        108, 109, 110, 111, 112, 113, 114, 115, 116, 117, 118, 119, 120, 121,
        122, 123, 124, 125, 126, 127, 128, 129, 130, 131, 132, 133, 134, 135,
        136, 137, 138, 139, 140, 141, 142, 143, 144, 145, 146, 147, 148, 149,
        150, 151, 152, 153, 154, 155, 156, 157, 158, 159, 160, 161, 162, 163,
        164, 165, 166, 167, 168, 169, 170, 171, 172, 173, 174, 175, 176, 177,
        178, 179, 180, 181, 182, 183, 184, 185, 186, 187, 188, 189, 190, 191,
        192, 193, 194, 195, 196, 197, 198, 199, 200, 201, 202, 203, 204, 205,
        206, 207, 208, 209, 210, 211, 212, 213, 214, 215, 216, 217, 218, 219,
        220, 221, 222, 223, 224, 225, 226, 227, 228, 229, 230, 231, 232, 233,
        234, 235, 236, 237, 238, 239, 240, 241, 242, 243, 244, 245, 246, 247,
        248, 249, 250, 251, 252, 253, 254, 255
      },
      .values_len = 256
    },
    .expected_output = {
      .bytes = (uint8_t []){0xff},
      .bytes_len = 1,
      .last_error_code = VtencErrorNoError
    }
  },
  {
    .input = {
      .encoder = {
        .has_repeated_values = 0,
        .skip_full_subtrees = 1
      },
      .values = (uint8_t []){33},
      .values_len = 1
    },
    .expected_output = {
      .bytes = (uint8_t []){0x00, 0x21},
      .bytes_len = 2,
      .last_error_code = VtencErrorNoError
    }
  },
  {
    .input = {
      .encoder = {
        .has_repeated_values = 0,
        .skip_full_subtrees = 1
      },
      .values = (uint8_t []){0, 1, 2, 3, 4, 5, 6, 7, 160, 161, 162, 163},
      .values_len = 12
    },
    .expected_output = {
      .bytes = (uint8_t []){0x0b, 0x48, 0x90, 0x44, 0x44, 0x04},
      .bytes_len = 6,
      .last_error_code = VtencErrorNoError
    }
  },
  {
    .input = {
      .encoder = {
        .has_repeated_values = 0,
        .skip_full_subtrees = 1
      },
      .values = (uint8_t []){13, 77, 88, 93, 149, 212},
      .values_len = 6
    },
    .expected_output = {
      .bytes = (uint8_t []){0x05, 0x8c, 0xaa, 0x72, 0x14, 0xdd, 0x00},
      .bytes_len = 7,
      .last_error_code = VtencErrorNoError
    }
  }
};

static struct EncodeTestCase test_cases16[] = {
  {
    .input = {
      .encoder = {
        .has_repeated_values = 1,
        .skip_full_subtrees = 0
      },
      .values = (uint16_t []){},
      .values_len = 0
    },
    .expected_output = {
      .bytes = (uint8_t []){0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
      .bytes_len = 8,
      .last_error_code = VtencErrorNoError
    }
  },
  {
    .input = {
      .encoder = {
        .has_repeated_values = 1,
        .skip_full_subtrees = 0
      },
      .values = (uint16_t []){13862},
      .values_len = 1
    },
    .expected_output = {
      .bytes = (uint8_t []){
        0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x4c, 0x6c, 0x00
      },
      .bytes_len = 10,
      .last_error_code = VtencErrorNoError
    }
  },
  {
    .input = {
      .encoder = {
        .has_repeated_values = 1,
        .skip_full_subtrees = 0
      },
      .values = (uint16_t []){1099, 2227, 8102, 27654, 29001, 35511, 50083},
      .values_len = 7
    },
    .expected_output = {
      .bytes = (uint8_t []){
        0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xda, 0xe8, 0x70, 0xab, 0x8c,
        0x92, 0xc2, 0x80, 0xd7, 0xf4, 0x9b, 0xc5, 0x12, 0x01
      },
      .bytes_len = 21,
      .last_error_code = VtencErrorNoError
    }
  },
  {
    .input = {
      .encoder = {
        .has_repeated_values = 1,
        .skip_full_subtrees = 0
      },
      .values = (uint16_t []){677, 677, 677, 8881, 8881, 8881, 8881, 8881},
      .values_len = 8
    },
    .expected_output = {
      .bytes = (uint8_t []){
        0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0xa7, 0x2d, 0x8a, 0x02,
        0x6d, 0xf1, 0x33, 0xf3, 0x0c
      },
      .bytes_len = 17,
      .last_error_code = VtencErrorNoError
    }
  },
  {
    .input = {
      .encoder = {
        .has_repeated_values = 0,
        .skip_full_subtrees = 1
      },
      .values = (uint16_t []){},
      .values_len = 0
    },
    .expected_output = {
      .bytes = (uint8_t []){},
      .bytes_len = 0,
      .last_error_code = VtencErrorInputTooSmall
    }
  },
  {
    .input = {
      .encoder = {
        .has_repeated_values = 0,
        .skip_full_subtrees = 1
      },
      .values = (uint16_t []){},
      .values_len = 65537
    },
    .expected_output = {
      .bytes = (uint8_t []){},
      .bytes_len = 0,
      .last_error_code = VtencErrorInputTooBig
    }
  },
  {
    .input = {
      .encoder = {
        .has_repeated_values = 0,
        .skip_full_subtrees = 1
      },
      .values = (uint16_t []){23091},
      .values_len = 1
    },
    .expected_output = {
      .bytes = (uint8_t []){0x00, 0x00, 0x33, 0x5a},
      .bytes_len = 4,
      .last_error_code = VtencErrorNoError
    }
  },
  {
    .input = {
      .encoder = {
        .has_repeated_values = 0,
        .skip_full_subtrees = 1
      },
      .values = (uint16_t []){1655, 3391, 4111, 8770, 29006, 32712, 32993, 58042},
      .values_len = 8
    },
    .expected_output = {
      .bytes = (uint8_t []){
        0x07, 0x00, 0x96, 0xae, 0x18, 0x0e, 0x10, 0x42, 0xbe, 0x53, 0x26, 0x24,
        0x7c, 0x80, 0x7e, 0x7a, 0x67
      },
      .bytes_len = 17,
      .last_error_code = VtencErrorNoError
    }
  },
  {
    .input = {
      .encoder = {
        .has_repeated_values = 0,
        .skip_full_subtrees = 1
      },
      .values = (uint16_t []){
        14000, 14001, 14002, 14003, 14004, 14005, 14006, 14007,
        20000, 20001, 20002, 20003
      },
      .values_len = 12
    },
    .expected_output = {
      .bytes = (uint8_t []){
        0x0b, 0x00, 0x8c, 0x24, 0x00, 0x92, 0x20, 0x09, 0x80, 0x00, 0x08, 0x08,
        0x80
      },
      .bytes_len = 13,
      .last_error_code = VtencErrorNoError
    }
  }
};

static struct EncodeTestCase test_cases32[] = {
  {
    .input = {
      .encoder = {
        .has_repeated_values = 1,
        .skip_full_subtrees = 0
      },
      .values = (uint32_t []){},
      .values_len = 0
    },
    .expected_output = {
      .bytes = (uint8_t []){0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
      .bytes_len = 8,
      .last_error_code = VtencErrorNoError
    }
  },
  {
    .input = {
      .encoder = {
        .has_repeated_values = 1,
        .skip_full_subtrees = 0
      },
      .values = (uint32_t []){726550617},
      .values_len = 1
    },
    .expected_output = {
      .bytes = (uint8_t []){
        0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xb2, 0x90, 0x9c, 0x56, 0x00
      },
      .bytes_len = 12,
      .last_error_code = VtencErrorNoError
    }
  },
  {
    .input = {
      .encoder = {
        .has_repeated_values = 1,
        .skip_full_subtrees = 0
      },
      .values = (uint32_t []){5348, 13089333, 88199704, 271008013, 1451881090},
      .values_len = 5
    },
    .expected_output = {
      .bytes = (uint8_t []){
        0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x4a, 0x41, 0xf9, 0x44, 0x8b,
        0x6b, 0x08, 0x3a, 0x81, 0xc5, 0x90, 0x0e, 0x4a, 0xab, 0xd1, 0x3d, 0x92,
        0x53, 0x00, 0x00
      },
      .bytes_len = 27,
      .last_error_code = VtencErrorNoError
    }
  },
  {
    .input = {
      .encoder = {
        .has_repeated_values = 1,
        .skip_full_subtrees = 0
      },
      .values = (uint32_t []){
        77865901, 77865901, 77865901, 77865901, 314976310, 314976310
      },
      .values_len = 6
    },
    .expected_output = {
      .bytes = (uint8_t []){
        0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x6c, 0x53, 0x11, 0x54, 0x50,
        0x11, 0x55, 0x41, 0x90, 0x20, 0x41, 0x90, 0x20, 0x49, 0x90, 0x04, 0x40,
        0x10, 0x20, 0x00
      },
      .bytes_len = 27,
      .last_error_code = VtencErrorNoError
    }
  },
  {
    .input = {
      .encoder = {
        .has_repeated_values = 0,
        .skip_full_subtrees = 1
      },
      .values = (uint32_t []){},
      .values_len = 0
    },
    .expected_output = {
      .bytes = (uint8_t []){},
      .bytes_len = 0,
      .last_error_code = VtencErrorInputTooSmall
    }
  },
  {
    .input = {
      .encoder = {
        .has_repeated_values = 0,
        .skip_full_subtrees = 1
      },
      .values = (uint32_t []){},
      .values_len = 0x200000000
    },
    .expected_output = {
      .bytes = (uint8_t []){},
      .bytes_len = 0,
      .last_error_code = VtencErrorInputTooBig
    }
  },
  {
    .input = {
      .encoder = {
        .has_repeated_values = 0,
        .skip_full_subtrees = 1
      },
      .values = (uint32_t []){0x77e3ba42},
      .values_len = 1
    },
    .expected_output = {
      .bytes = (uint8_t []){0x00, 0x00, 0x00, 0x00, 0x42, 0xba, 0xe3, 0x77},
      .bytes_len = 8,
      .last_error_code = VtencErrorNoError
    }
  },
  {
    .input = {
      .encoder = {
        .has_repeated_values = 0,
        .skip_full_subtrees = 1
      },
      .values = (uint32_t []){
        0x98b204, 0x122fabb4, 0x378ecef0, 0x77ccab8f, 0xa40609bb
      },
      .values_len = 5
    },
    .expected_output = {
      .bytes = (uint8_t []){
        0x04, 0x00, 0x00, 0x00, 0xdc, 0x4d, 0x30, 0x20, 0xed, 0x71, 0x95, 0xf9,
        0x16, 0xde, 0xd9, 0xf1, 0x46, 0xbb, 0xfa, 0x22, 0x04, 0xb2, 0x98, 0x00
      },
      .bytes_len = 24,
      .last_error_code = VtencErrorNoError
    }
  },
  {
    .input = {
      .encoder = {
        .has_repeated_values = 0,
        .skip_full_subtrees = 1
      },
      .values = (uint32_t []){
        0xa500, 0xa501, 0xa502, 0xa503,
        0x4bbb00, 0x4bbb01,
        0xffff00, 0xffff01, 0xffff02, 0xffff03, 0xffff04, 0xffff05, 0xffff06, 0xffff07
      },
      .values_len = 14
    },
    .expected_output = {
      .bytes = (uint8_t []){
        0x0d, 0x00, 0x00, 0x00, 0xee, 0xee, 0xee, 0xee, 0x06, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x88, 0x88, 0x48, 0x45, 0x40, 0x40, 0x50, 0x55,
        0x49, 0x92, 0x04, 0x41, 0x82, 0x20, 0x49, 0x12
      },
      .bytes_len = 32,
      .last_error_code = VtencErrorNoError
    }
  }
};

static struct EncodeTestCase test_cases64[] = {
  {
    .input = {
      .encoder = {
        .has_repeated_values = 1,
        .skip_full_subtrees = 0
      },
      .values = (uint64_t []){},
      .values_len = 0
    },
    .expected_output = {
      .bytes = (uint8_t []){0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
      .bytes_len = 8,
      .last_error_code = VtencErrorNoError
    }
  },
  {
    .input = {
      .encoder = {
        .has_repeated_values = 1,
        .skip_full_subtrees = 0
      },
      .values = (uint64_t []){0xab778190fec42261ULL},
      .values_len = 1
    },
    .expected_output = {
      .bytes = (uint8_t []){
        0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc2, 0x44, 0x88, 0xfd, 0x21,
        0x03, 0xef, 0x56, 0x01
      },
      .bytes_len = 16,
      .last_error_code = VtencErrorNoError
    }
  },
  {
    .input = {
      .encoder = {
        .has_repeated_values = 1,
        .skip_full_subtrees = 0
      },
      .values = (uint64_t []){
        0x12a6ULL, 0x8addf0ULL, 0xffa1b4bbULL, 0x21258ee39aaaULL
      },
      .values_len = 4
    },
    .expected_output = {
      .bytes = (uint8_t []){
        0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x48, 0x92, 0x24, 0x49, 0x92,
        0x24, 0xc9, 0xa9, 0x6a, 0x8e, 0x3b, 0x96, 0x84, 0xff, 0xff, 0xff, 0xdd,
        0xa5, 0x0d, 0xfd, 0xab, 0xaa, 0xc1, 0x77, 0x2b, 0x4c, 0x25, 0x00
      },
      .bytes_len = 35,
      .last_error_code = VtencErrorNoError
    }
  },
  {
    .input = {
      .encoder = {
        .has_repeated_values = 1,
        .skip_full_subtrees = 0
      },
      .values = (uint64_t []){
        0x55555555ULL, 0x55555555ULL, 0x55555555ULL,
        0x111111111111ULL, 0x111111111111ULL
      },
      .values_len = 5
    },
    .expected_output = {
      .bytes = (uint8_t []){
        0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xda, 0xb6, 0x6d, 0xdb, 0xb6,
        0x6d, 0xdb, 0x4e, 0x45, 0x45, 0x45, 0x45, 0x45, 0x45, 0x45, 0x45, 0x45,
        0x45, 0xe5, 0xff, 0xff, 0x7f, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66,
        0x06
      },
      .bytes_len = 37,
      .last_error_code = VtencErrorNoError
    }
  },
  {
    .input = {
      .encoder = {
        .has_repeated_values = 0,
        .skip_full_subtrees = 1
      },
      .values = (uint64_t []){},
      .values_len = 0
    },
    .expected_output = {
      .bytes = (uint8_t []){},
      .bytes_len = 0,
      .last_error_code = VtencErrorInputTooSmall
    }
  },
  {
    .input = {
      .encoder = {
        .has_repeated_values = 0,
        .skip_full_subtrees = 1
      },
      .values = (uint64_t []){0x1122334455667788ULL},
      .values_len = 1
    },
    .expected_output = {
      .bytes = (uint8_t []){
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0xef, 0xcc, 0xaa, 0x88,
        0x66, 0x44, 0x22, 0x00
      },
      .bytes_len = 16,
      .last_error_code = VtencErrorNoError
    }
  },
  {
    .input = {
      .encoder = {
        .has_repeated_values = 0,
        .skip_full_subtrees = 1
      },
      .values = (uint64_t []){
        0x11223344ULL, 0xaabbccddULL, 0x1010101010ULL, 0x5555555555ULL, 0xf0f0f0f0f0ULL,
        0x998877665544ULL, 0xffeeffeeffeeULL
      },
      .values_len = 7
    },
    .expected_output = {
      .bytes = (uint8_t []){
        0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfe, 0xff, 0xff, 0xff, 0xff,
        0xff, 0x9b, 0xfb, 0xbf, 0xfb, 0xbf, 0xfb, 0x4f, 0x54, 0x65, 0x76, 0x87,
        0x98, 0xb5, 0x6d, 0x5b, 0xc2, 0xc3, 0xc3, 0xc3, 0xc3, 0x57, 0x55, 0x55,
        0x55, 0x55, 0x2d, 0x04, 0x04, 0x04, 0x04, 0xa8, 0xd6, 0xcd, 0xbc, 0xab,
        0x22, 0x9a, 0x11, 0x89, 0x00
      },
      .bytes_len = 53,
      .last_error_code = VtencErrorNoError
    }
  },
  {
    .input = {
      .encoder = {
        .has_repeated_values = 0,
        .skip_full_subtrees = 1
      },
      .values = (uint64_t []){
        0x20000000ULL, 0x20000001ULL, 0x20000002ULL, 0x20000003ULL,
        0x80000000ULL, 0x80000001ULL,
        0x2000000000ULL, 0x2000000001ULL
      },
      .values_len = 8
    },
    .expected_output = {
      .bytes = (uint8_t []){
        0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x11, 0x11, 0x11, 0x11,
        0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x4d, 0x55, 0x55, 0x55,
        0x55, 0x55, 0x55, 0x55, 0x55, 0xd5, 0xb6, 0x4d, 0x55, 0x55, 0x55, 0x55,
        0x55, 0x55, 0x55, 0x25, 0x48, 0x92, 0x24, 0x49, 0x92, 0x24, 0x49, 0x92,
        0x24, 0x49, 0x02
      },
      .bytes_len = 51,
      .last_error_code = VtencErrorNoError
    }
  }
};

int vtenc_encode8_test_case(struct EncodeTestCase *test_case)
{
  struct EncodeTestCaseInput *input = &(test_case->input);
  struct EncodeTestCaseOutput *expected_output = &(test_case->expected_output);
  VtencEncoder *encoder = &(input->encoder);
  const size_t out_cap = vtenc_max_encoded_size8(encoder, input->values_len);
  uint8_t out[out_cap & 0xffff]; // mask capacity to avoid large allocations on the stack
  size_t out_len;

  out_len = vtenc_encode8(
    encoder,
    input->values,
    input->values_len,
    out,
    out_cap
  );

  EXPECT_TRUE(out_len == expected_output->bytes_len);
  EXPECT_TRUE(memcmp(out, expected_output->bytes, expected_output->bytes_len) == 0);
  EXPECT_TRUE(encoder->last_error_code == expected_output->last_error_code);

  return 1;
}

int vtenc_encode16_test_case(struct EncodeTestCase *test_case)
{
  struct EncodeTestCaseInput *input = &(test_case->input);
  struct EncodeTestCaseOutput *expected_output = &(test_case->expected_output);
  VtencEncoder *encoder = &(input->encoder);
  const size_t out_cap = vtenc_max_encoded_size16(encoder, input->values_len);
  uint8_t out[out_cap & 0xffff]; // mask capacity to avoid large allocations on the stack
  size_t out_len;

  out_len = vtenc_encode16(
    encoder,
    input->values,
    input->values_len,
    out,
    out_cap
  );

  EXPECT_TRUE(out_len == expected_output->bytes_len);
  EXPECT_TRUE(memcmp(out, expected_output->bytes, expected_output->bytes_len) == 0);
  EXPECT_TRUE(encoder->last_error_code == expected_output->last_error_code);

  return 1;
}

int vtenc_encode32_test_case(struct EncodeTestCase *test_case)
{
  struct EncodeTestCaseInput *input = &(test_case->input);
  struct EncodeTestCaseOutput *expected_output = &(test_case->expected_output);
  VtencEncoder *encoder = &(input->encoder);
  const size_t out_cap = vtenc_max_encoded_size32(encoder, input->values_len);
  uint8_t out[out_cap & 0xffff]; // mask capacity to avoid large allocations on the stack
  size_t out_len;

  out_len = vtenc_encode32(
    encoder,
    input->values,
    input->values_len,
    out,
    out_cap
  );

  EXPECT_TRUE(out_len == expected_output->bytes_len);
  EXPECT_TRUE(memcmp(out, expected_output->bytes, expected_output->bytes_len) == 0);
  EXPECT_TRUE(encoder->last_error_code == expected_output->last_error_code);

  return 1;
}

int vtenc_encode64_test_case(struct EncodeTestCase *test_case)
{
  struct EncodeTestCaseInput *input = &(test_case->input);
  struct EncodeTestCaseOutput *expected_output = &(test_case->expected_output);
  VtencEncoder *encoder = &(input->encoder);
  const size_t out_cap = vtenc_max_encoded_size64(encoder, input->values_len);
  uint8_t out[out_cap & 0xffff]; // mask capacity to avoid large allocations on the stack
  size_t out_len;

  out_len = vtenc_encode64(
    encoder,
    input->values,
    input->values_len,
    out,
    out_cap
  );

  EXPECT_TRUE(out_len == expected_output->bytes_len);
  EXPECT_TRUE(memcmp(out, expected_output->bytes, expected_output->bytes_len) == 0);
  EXPECT_TRUE(encoder->last_error_code == expected_output->last_error_code);

  return 1;
}

int test_vtenc_encode8(void)
{
  const size_t test_cases8_size = sizeof(test_cases8) / sizeof(test_cases8[0]);
  size_t i;

  for (i = 0; i < test_cases8_size; ++i) {
    EXPECT_TRUE(vtenc_encode8_test_case(&test_cases8[i]));
  }

  return 1;
}

int test_vtenc_encode16(void)
{
  const size_t test_cases16_size = sizeof(test_cases16) / sizeof(test_cases16[0]);
  size_t i;

  for (i = 0; i < test_cases16_size; ++i) {
    EXPECT_TRUE(vtenc_encode16_test_case(&test_cases16[i]));
  }

  return 1;
}

int test_vtenc_encode32(void)
{
  const size_t test_cases32_size = sizeof(test_cases32) / sizeof(test_cases32[0]);
  size_t i;

  for (i = 0; i < test_cases32_size; ++i) {
    EXPECT_TRUE(vtenc_encode32_test_case(&test_cases32[i]));
  }

  return 1;
}

int test_vtenc_encode64(void)
{
  const size_t test_cases64_size = sizeof(test_cases64) / sizeof(test_cases64[0]);
  size_t i;

  for (i = 0; i < test_cases64_size; ++i) {
    EXPECT_TRUE(vtenc_encode64_test_case(&test_cases64[i]));
  }

  return 1;
}

int test_vtenc_max_encoded_size8(void)
{
  VtencEncoder enc = {.has_repeated_values = 1};

  EXPECT_TRUE(vtenc_max_encoded_size8(&enc, 0) == 8);
  EXPECT_TRUE(vtenc_max_encoded_size8(&enc, 1) == 16);
  EXPECT_TRUE(vtenc_max_encoded_size8(&enc, 5) == 16);
  EXPECT_TRUE(vtenc_max_encoded_size8(&enc, 10) == 24);
  EXPECT_TRUE(vtenc_max_encoded_size8(&enc, 100) == 112);
  EXPECT_TRUE(vtenc_max_encoded_size8(&enc, 1000) == 1008);

  enc.has_repeated_values = 0;

  EXPECT_TRUE(vtenc_max_encoded_size8(&enc, 0) == 8);
  EXPECT_TRUE(vtenc_max_encoded_size8(&enc, 1) == 8);
  EXPECT_TRUE(vtenc_max_encoded_size8(&enc, 5) == 8);
  EXPECT_TRUE(vtenc_max_encoded_size8(&enc, 10) == 16);
  EXPECT_TRUE(vtenc_max_encoded_size8(&enc, 100) == 104);

  return 1;
}

int test_vtenc_max_encoded_size16(void)
{
  VtencEncoder enc = {.has_repeated_values = 1};

  EXPECT_TRUE(vtenc_max_encoded_size16(&enc, 0) == 16);
  EXPECT_TRUE(vtenc_max_encoded_size16(&enc, 1) == 16);
  EXPECT_TRUE(vtenc_max_encoded_size16(&enc, 5) == 24);
  EXPECT_TRUE(vtenc_max_encoded_size16(&enc, 10) == 32);
  EXPECT_TRUE(vtenc_max_encoded_size16(&enc, 100) == 216);
  EXPECT_TRUE(vtenc_max_encoded_size16(&enc, 1000) == 2016);

  enc.has_repeated_values = 0;

  EXPECT_TRUE(vtenc_max_encoded_size16(&enc, 0) == 8);
  EXPECT_TRUE(vtenc_max_encoded_size16(&enc, 1) == 8);
  EXPECT_TRUE(vtenc_max_encoded_size16(&enc, 5) == 16);
  EXPECT_TRUE(vtenc_max_encoded_size16(&enc, 10) == 24);
  EXPECT_TRUE(vtenc_max_encoded_size16(&enc, 100) == 208);
  EXPECT_TRUE(vtenc_max_encoded_size16(&enc, 1000) == 2008);

  return 1;
}

int test_vtenc_max_encoded_size32(void)
{
  VtencEncoder enc = {.has_repeated_values = 1};

  EXPECT_TRUE(vtenc_max_encoded_size32(&enc, 0) == 16);
  EXPECT_TRUE(vtenc_max_encoded_size32(&enc, 1) == 16);
  EXPECT_TRUE(vtenc_max_encoded_size32(&enc, 5) == 32);
  EXPECT_TRUE(vtenc_max_encoded_size32(&enc, 10) == 56);
  EXPECT_TRUE(vtenc_max_encoded_size32(&enc, 100) == 416);
  EXPECT_TRUE(vtenc_max_encoded_size32(&enc, 1000) == 4016);

  enc.has_repeated_values = 0;

  EXPECT_TRUE(vtenc_max_encoded_size32(&enc, 0) == 8);
  EXPECT_TRUE(vtenc_max_encoded_size32(&enc, 1) == 16);
  EXPECT_TRUE(vtenc_max_encoded_size32(&enc, 5) == 32);
  EXPECT_TRUE(vtenc_max_encoded_size32(&enc, 10) == 48);
  EXPECT_TRUE(vtenc_max_encoded_size32(&enc, 100) == 408);
  EXPECT_TRUE(vtenc_max_encoded_size32(&enc, 1000) == 4008);

  return 1;
}

int test_vtenc_max_encoded_size64(void)
{
  VtencEncoder enc = {.has_repeated_values = 1};

  EXPECT_TRUE(vtenc_max_encoded_size64(&enc, 0) == 16);
  EXPECT_TRUE(vtenc_max_encoded_size64(&enc, 1) == 24);
  EXPECT_TRUE(vtenc_max_encoded_size64(&enc, 5) == 56);
  EXPECT_TRUE(vtenc_max_encoded_size64(&enc, 10) == 96);
  EXPECT_TRUE(vtenc_max_encoded_size64(&enc, 100) == 816);
  EXPECT_TRUE(vtenc_max_encoded_size64(&enc, 1000) == 8016);

  enc.has_repeated_values = 0;

  EXPECT_TRUE(vtenc_max_encoded_size64(&enc, 0) == 16);
  EXPECT_TRUE(vtenc_max_encoded_size64(&enc, 1) == 24);
  EXPECT_TRUE(vtenc_max_encoded_size64(&enc, 5) == 56);
  EXPECT_TRUE(vtenc_max_encoded_size64(&enc, 10) == 96);
  EXPECT_TRUE(vtenc_max_encoded_size64(&enc, 100) == 816);
  EXPECT_TRUE(vtenc_max_encoded_size64(&enc, 1000) == 8016);

  return 1;
}
