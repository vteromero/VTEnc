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
