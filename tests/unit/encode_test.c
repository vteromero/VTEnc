/**
  Copyright (c) 2019 Vicente Romero Calero. All rights reserved.
  Licensed under the MIT License.
  See LICENSE file in the project root for full license information.
 */
#include <stdlib.h>
#include <string.h>

#include "unit_tests.h"
#include "../../vtenc.h"

int test_vtenc_list_encode_u8_1(void)
{
  const uint8_t in[] = {};
  const size_t in_len = sizeof(in);
  const size_t out_cap = vtenc_list_max_encoded_size_u8(in_len);
  uint8_t out[out_cap];
  size_t out_len;
  const uint8_t expected_out[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
  const size_t expected_out_len = sizeof(expected_out);

  EXPECT_TRUE(vtenc_list_encode_u8(in, in_len, out, out_cap, &out_len) == VtencErrorNoError);
  EXPECT_TRUE(out_len == expected_out_len);
  EXPECT_TRUE(memcmp(out, expected_out, expected_out_len) == 0);

  return 1;
}

int test_vtenc_list_encode_u8_2(void)
{
  const uint8_t in[] = {5, 22, 23, 44, 62, 69, 109, 113, 178, 194, 206};
  const size_t in_len = sizeof(in);
  const size_t out_cap = vtenc_list_max_encoded_size_u8(in_len);
  uint8_t out[out_cap];
  size_t out_len;
  const uint8_t expected_out[] = {
    0x0b, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xb0, 0x56, 0x09, 0xc5, 0xd8,
    0x8a, 0x2e, 0x56, 0x2b, 0x01
  };
  const size_t expected_out_len = sizeof(expected_out);

  EXPECT_TRUE(vtenc_list_encode_u8(in, in_len, out, out_cap, &out_len) == VtencErrorNoError);
  EXPECT_TRUE(out_len == expected_out_len);
  EXPECT_TRUE(memcmp(out, expected_out, expected_out_len) == 0);

  return 1;
}

int test_vtenc_list_encode_u8_3(void)
{
  const uint8_t in[] = {57, 57, 57, 111, 111, 111, 111, 208, 208};
  const size_t in_len = sizeof(in);
  const size_t out_cap = vtenc_list_max_encoded_size_u8(in_len);
  uint8_t out[out_cap];
  size_t out_len;
  const uint8_t expected_out[] = {
    0x09, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x6e, 0xc0, 0x03, 0x02, 0x00,
    0xa2, 0x0a
  };
  const size_t expected_out_len = sizeof(expected_out);

  EXPECT_TRUE(vtenc_list_encode_u8(in, in_len, out, out_cap, &out_len) == VtencErrorNoError);
  EXPECT_TRUE(out_len == expected_out_len);
  EXPECT_TRUE(memcmp(out, expected_out, expected_out_len) == 0);

  return 1;
}

int test_vtenc_list_encode_u16_1(void)
{
  const uint16_t in[] = {};
  const size_t in_len = 0;
  const size_t out_cap = vtenc_list_max_encoded_size_u16(in_len);
  uint8_t out[out_cap];
  size_t out_len;
  const uint8_t expected_out[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
  const size_t expected_out_len = sizeof(expected_out);

  EXPECT_TRUE(vtenc_list_encode_u16(in, in_len, out, out_cap, &out_len) == VtencErrorNoError);
  EXPECT_TRUE(out_len == expected_out_len);
  EXPECT_TRUE(memcmp(out, expected_out, expected_out_len) == 0);

  return 1;
}

int test_vtenc_list_encode_u16_2(void)
{
  const uint16_t in[] = {1099, 2227, 8102, 27654, 29001, 35511, 50083};
  const size_t in_len = sizeof(in) / sizeof(in[0]);
  const size_t out_cap = vtenc_list_max_encoded_size_u16(in_len);
  uint8_t out[out_cap];
  size_t out_len;
  const uint8_t expected_out[] = {
    0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xba, 0xcd, 0x2d, 0x97, 0x01,
    0x4d, 0xe2, 0xcf, 0x6b, 0x6b, 0x95, 0x78, 0x74, 0x00
  };
  const size_t expected_out_len = sizeof(expected_out);

  EXPECT_TRUE(vtenc_list_encode_u16(in, in_len, out, out_cap, &out_len) == VtencErrorNoError);
  EXPECT_TRUE(out_len == expected_out_len);
  EXPECT_TRUE(memcmp(out, expected_out, expected_out_len) == 0);

  return 1;
}

int test_vtenc_list_encode_u16_3(void)
{
  const uint16_t in[] = {677, 677, 677, 8881, 8881, 8881, 8881, 8881};
  const size_t in_len = sizeof(in) / sizeof(in[0]);
  const size_t out_cap = vtenc_list_max_encoded_size_u16(in_len);
  uint8_t out[out_cap];
  size_t out_len;
  const uint8_t expected_out[] = {
    0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0xe7, 0x67, 0xe6, 0x99,
    0xb6, 0x28, 0x0a, 0xb4, 0x05
  };
  const size_t expected_out_len = sizeof(expected_out);

  EXPECT_TRUE(vtenc_list_encode_u16(in, in_len, out, out_cap, &out_len) == VtencErrorNoError);
  EXPECT_TRUE(out_len == expected_out_len);
  EXPECT_TRUE(memcmp(out, expected_out, expected_out_len) == 0);

  return 1;
}

int test_vtenc_list_encode_u32_1(void)
{
  const uint32_t in[] = {};
  const size_t in_len = 0;
  const size_t out_cap = vtenc_list_max_encoded_size_u32(in_len);
  uint8_t out[out_cap];
  size_t out_len;
  const uint8_t expected_out[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
  const size_t expected_out_len = sizeof(expected_out);

  EXPECT_TRUE(vtenc_list_encode_u32(in, in_len, out, out_cap, &out_len) == VtencErrorNoError);
  EXPECT_TRUE(out_len == expected_out_len);
  EXPECT_TRUE(memcmp(out, expected_out, expected_out_len) == 0);

  return 1;
}

int test_vtenc_list_encode_u32_2(void)
{
  const uint32_t in[] = {5348, 13089333, 88199704, 271008013, 1451881090};
  const size_t in_len = sizeof(in) / sizeof(in[0]);
  const size_t out_cap = vtenc_list_max_encoded_size_u32(in_len);
  uint8_t out[out_cap];
  size_t out_len;
  const uint8_t expected_out[] = {
    0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x4a, 0x6e, 0xb5, 0xff, 0x35,
    0xb6, 0x43, 0x74, 0xaa, 0x3e, 0xda, 0xf3, 0xdf, 0xe8, 0x7b, 0x2a, 0xdd,
    0x60, 0x7d, 0x01
  };
  const size_t expected_out_len = sizeof(expected_out);

  EXPECT_TRUE(vtenc_list_encode_u32(in, in_len, out, out_cap, &out_len) == VtencErrorNoError);
  EXPECT_TRUE(out_len == expected_out_len);
  EXPECT_TRUE(memcmp(out, expected_out, expected_out_len) == 0);

  return 1;
}

int test_vtenc_list_encode_u32_3(void)
{
  const uint32_t in[] = {77865901, 77865901, 77865901, 77865901, 314976310, 314976310};
  const size_t in_len = sizeof(in) / sizeof(in[0]);
  const size_t out_cap = vtenc_list_max_encoded_size_u32(in_len);
  uint8_t out[out_cap];
  size_t out_len;
  const uint8_t expected_out[] = {
    0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x6c, 0x93, 0x20, 0x41, 0x90,
    0x20, 0x49, 0x90, 0x04, 0x40, 0x10, 0x20, 0x14, 0x41, 0x05, 0x15, 0x51,
    0x15, 0x04, 0x01
  };
  const size_t expected_out_len = sizeof(expected_out);

  EXPECT_TRUE(vtenc_list_encode_u32(in, in_len, out, out_cap, &out_len) == VtencErrorNoError);
  EXPECT_TRUE(out_len == expected_out_len);
  EXPECT_TRUE(memcmp(out, expected_out, expected_out_len) == 0);

  return 1;
}

int test_vtenc_list_encode_u64_1(void)
{
  const uint64_t in[] = {};
  const size_t in_len = 0;
  const size_t out_cap = vtenc_list_max_encoded_size_u64(in_len);
  uint8_t out[out_cap];
  size_t out_len;
  const uint8_t expected_out[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
  const size_t expected_out_len = sizeof(expected_out);

  EXPECT_TRUE(vtenc_list_encode_u64(in, in_len, out, out_cap, &out_len) == VtencErrorNoError);
  EXPECT_TRUE(out_len == expected_out_len);
  EXPECT_TRUE(memcmp(out, expected_out, expected_out_len) == 0);

  return 1;
}

int test_vtenc_list_encode_u64_2(void)
{
  const uint64_t in[] = {0x12a6, 0x8addf0, 0xffa1b4bb, 0x21258ee39aaa};
  const size_t in_len = sizeof(in) / sizeof(in[0]);
  const size_t out_cap = vtenc_list_max_encoded_size_u64(in_len);
  uint8_t out[out_cap];
  size_t out_len;
  const uint8_t expected_out[] = {
    0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x48, 0x92, 0x24, 0x49, 0x92,
    0x24, 0xc9, 0xfd, 0xff, 0xff, 0xaf, 0xaa, 0xda, 0xff, 0x56, 0xf3, 0x4a,
    0x04, 0x0f, 0xd0, 0x93, 0x16, 0x79, 0x5b, 0x8e, 0x38, 0xa6, 0xaa
  };
  const size_t expected_out_len = sizeof(expected_out);

  EXPECT_TRUE(vtenc_list_encode_u64(in, in_len, out, out_cap, &out_len) == VtencErrorNoError);
  EXPECT_TRUE(out_len == expected_out_len);
  EXPECT_TRUE(memcmp(out, expected_out, expected_out_len) == 0);

  return 1;
}

int test_vtenc_list_encode_u64_3(void)
{
  const uint64_t in[] = {0x55555555, 0x55555555, 0x55555555, 0x111111111111, 0x111111111111};
  const size_t in_len = sizeof(in) / sizeof(in[0]);
  const size_t out_cap = vtenc_list_max_encoded_size_u64(in_len);
  uint8_t out[out_cap];
  size_t out_len;
  const uint8_t expected_out[] = {
    0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xda, 0xb6, 0x6d, 0xdb, 0xb6,
    0x6d, 0xdb, 0xee, 0xff, 0xff, 0x7f, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66,
    0x66, 0x46, 0x45, 0x45, 0x45, 0x45, 0x45, 0x45, 0x45, 0x45, 0x45, 0x45,
    0x05
  };
  const size_t expected_out_len = sizeof(expected_out);

  EXPECT_TRUE(vtenc_list_encode_u64(in, in_len, out, out_cap, &out_len) == VtencErrorNoError);
  EXPECT_TRUE(out_len == expected_out_len);
  EXPECT_TRUE(memcmp(out, expected_out, expected_out_len) == 0);

  return 1;
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
  const size_t out_cap = vtenc_set_max_encoded_size_u8(in_len);
  uint8_t out[out_cap];
  size_t out_len, i;
  const uint8_t expected_out[] = {0xff};
  const size_t expected_out_len = sizeof(expected_out);

  for (i=0; i<in_len; ++i) in[i] = (uint8_t)i;

  EXPECT_TRUE(vtenc_set_encode_u8(in, in_len, out, out_cap, &out_len) == VtencErrorNoError);
  EXPECT_TRUE(out_len == expected_out_len);
  EXPECT_TRUE(memcmp(out, expected_out, expected_out_len) == 0);

  return 1;
}

int test_vtenc_set_encode_u8_4(void)
{
  const uint8_t in[] = {33};
  const size_t in_len = sizeof(in);
  const size_t out_cap = vtenc_set_max_encoded_size_u8(in_len);
  uint8_t out[out_cap];
  size_t out_len;
  const uint8_t expected_out[] = {0x00, 0x7b};
  const size_t expected_out_len = sizeof(expected_out);

  EXPECT_TRUE(vtenc_set_encode_u8(in, in_len, out, out_cap, &out_len) == VtencErrorNoError);
  EXPECT_TRUE(out_len == expected_out_len);
  EXPECT_TRUE(memcmp(out, expected_out, expected_out_len) == 0);

  return 1;
}

int test_vtenc_set_encode_u8_5(void)
{
  const uint8_t in[] = {0, 1, 2, 3, 4, 5, 6, 7, 160, 161, 162, 163};
  const size_t in_len = sizeof(in);
  const size_t out_cap = vtenc_set_max_encoded_size_u8(in_len);
  uint8_t out[out_cap];
  size_t out_len;
  const uint8_t expected_out[] = {0x0b, 0x88, 0x88, 0x48, 0x90, 0x04};
  const size_t expected_out_len = sizeof(expected_out);

  EXPECT_TRUE(vtenc_set_encode_u8(in, in_len, out, out_cap, &out_len) == VtencErrorNoError);
  EXPECT_TRUE(out_len == expected_out_len);
  EXPECT_TRUE(memcmp(out, expected_out, expected_out_len) == 0);

  return 1;
}

int test_vtenc_set_encode_u8_6(void)
{
  const uint8_t in[] = {13, 77, 88, 93, 149, 212};
  const size_t in_len = sizeof(in);
  const size_t out_cap = vtenc_set_max_encoded_size_u8(in_len);
  uint8_t out[out_cap];
  size_t out_len;
  const uint8_t expected_out[] = {0x05, 0xcc, 0x74, 0x44, 0x57, 0x55, 0x03};
  const size_t expected_out_len = sizeof(expected_out);

  EXPECT_TRUE(vtenc_set_encode_u8(in, in_len, out, out_cap, &out_len) == VtencErrorNoError);
  EXPECT_TRUE(out_len == expected_out_len);
  EXPECT_TRUE(memcmp(out, expected_out, expected_out_len) == 0);

  return 1;
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
  const uint16_t in[] = {1655, 3391, 4111, 8770, 29006, 32712, 32993, 58042};
  const size_t in_len = sizeof(in) / sizeof(in[0]);
  const size_t out_cap = vtenc_set_max_encoded_size_u16(in_len);
  uint8_t out[out_cap];
  size_t out_len;
  const uint8_t expected_out[] = {
    0x07, 0x00, 0xc6, 0x19, 0x23, 0x34, 0xf0, 0x0f, 0xb7, 0x17, 0x5a, 0x23,
    0xd8, 0xfb, 0xf1, 0x5c, 0x51
  };
  const size_t expected_out_len = sizeof(expected_out);

  EXPECT_TRUE(vtenc_set_encode_u16(in, in_len, out, out_cap, &out_len) == VtencErrorNoError);
  EXPECT_TRUE(out_len == expected_out_len);
  EXPECT_TRUE(memcmp(out, expected_out, expected_out_len) == 0);

  return 1;
}

int test_vtenc_set_encode_u16_4(void)
{
  const uint16_t in[] = {
    14000, 14001, 14002, 14003, 14004, 14005, 14006, 14007,
    20000, 20001, 20002, 20003
  };
  const size_t in_len = sizeof(in) / sizeof(in[0]);
  const size_t out_cap = vtenc_set_max_encoded_size_u16(in_len);
  uint8_t out[out_cap];
  size_t out_len;
  const uint8_t expected_out[] = {
    0x0b, 0x00, 0x8c, 0x00, 0x08, 0x80, 0x80, 0x00, 0x48, 0x02, 0x20, 0x09,
    0x92
  };
  const size_t expected_out_len = sizeof(expected_out);

  EXPECT_TRUE(vtenc_set_encode_u16(in, in_len, out, out_cap, &out_len) == VtencErrorNoError);
  EXPECT_TRUE(out_len == expected_out_len);
  EXPECT_TRUE(memcmp(out, expected_out, expected_out_len) == 0);

  return 1;
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
  const uint32_t in[] = {0x98b204, 0x122fabb4, 0x378ecef0, 0x77ccab8f, 0xa40609bb};
  const size_t in_len = sizeof(in) / sizeof(in[0]);
  const size_t out_cap = vtenc_set_max_encoded_size_u32(in_len);
  uint8_t out[out_cap];
  size_t out_len;
  const uint8_t expected_out[] = {
    0x04, 0x00, 0x00, 0x00, 0x9c, 0xbd, 0xb9, 0xec, 0xf7, 0x2e, 0xa8, 0x48,
    0x0b, 0x47, 0x46, 0x78, 0x82, 0x59, 0xc5, 0xa1, 0xfd, 0xf9, 0x26, 0x02
  };
  const size_t expected_out_len = sizeof(expected_out);

  EXPECT_TRUE(vtenc_set_encode_u32(in, in_len, out, out_cap, &out_len) == VtencErrorNoError);
  EXPECT_TRUE(out_len == expected_out_len);
  EXPECT_TRUE(memcmp(out, expected_out, expected_out_len) == 0);

  return 1;
}

int test_vtenc_set_encode_u32_4(void)
{
  const uint32_t in[] = {
    0xa500, 0xa501, 0xa502, 0xa503,
    0x4bbb00, 0x4bbb01,
    0xffff00, 0xffff01, 0xffff02, 0xffff03, 0xffff04, 0xffff05, 0xffff06, 0xffff07
  };
  const size_t in_len = sizeof(in) / sizeof(in[0]);
  const size_t out_cap = vtenc_set_max_encoded_size_u32(in_len);
  uint8_t out[out_cap];
  size_t out_len;
  const uint8_t expected_out[] = {
    0x0d, 0x00, 0x00, 0x00, 0xee, 0xee, 0xee, 0xee, 0x46, 0x92, 0x24, 0x41,
    0x90, 0x20, 0x48, 0x92, 0x54, 0x04, 0x04, 0x04, 0x55, 0x15, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x11, 0x11
  };
  const size_t expected_out_len = sizeof(expected_out);

  EXPECT_TRUE(vtenc_set_encode_u32(in, in_len, out, out_cap, &out_len) == VtencErrorNoError);
  EXPECT_TRUE(out_len == expected_out_len);
  EXPECT_TRUE(memcmp(out, expected_out, expected_out_len) == 0);

  return 1;
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
  const uint64_t in[] = {
    0x11223344ULL, 0xaabbccddULL, 0x1010101010ULL, 0x5555555555ULL, 0xf0f0f0f0f0ULL,
    0x998877665544ULL, 0xffeeffeeffeeULL
  };
  const size_t in_len = sizeof(in) / sizeof(in[0]);
  const size_t out_cap = vtenc_set_max_encoded_size_u64(in_len);
  uint8_t out[out_cap];
  size_t out_len;
  const uint8_t expected_out[] = {
    0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfe, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xdb, 0xb6, 0x6d, 0xb9, 0x55, 0x6d, 0xb7, 0x3b, 0xd3, 0x5d, 0x15,
    0x61, 0x26, 0xfa, 0xfb, 0xfb, 0xfb, 0xfb, 0xaa, 0xaa, 0xaa, 0xaa, 0x0a,
    0x0f, 0x0f, 0x0f, 0x0f, 0x5f, 0xe6, 0x1e, 0x91, 0x59, 0xd5, 0x0d, 0x20,
    0x02, 0x20, 0x02, 0x20, 0x02
  };
  const size_t expected_out_len = sizeof(expected_out);

  EXPECT_TRUE(vtenc_set_encode_u64(in, in_len, out, out_cap, &out_len) == VtencErrorNoError);
  EXPECT_TRUE(out_len == expected_out_len);
  EXPECT_TRUE(memcmp(out, expected_out, expected_out_len) == 0);

  return 1;
}

int test_vtenc_set_encode_u64_3(void)
{
  const uint64_t in[] = {
    0x20000000ULL, 0x20000001ULL, 0x20000002ULL, 0x20000003ULL,
    0x80000000ULL, 0x80000001ULL,
    0x2000000000ULL, 0x2000000001ULL
  };
  const size_t in_len = sizeof(in) / sizeof(in[0]);
  const size_t out_cap = vtenc_set_max_encoded_size_u64(in_len);
  uint8_t out[out_cap];
  size_t out_len;
  const uint8_t expected_out[] = {
    0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x11, 0x11, 0x11, 0x11,
    0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0xcd, 0xb6, 0x4d, 0x82,
    0x24, 0x49, 0x92, 0x24, 0x49, 0x92, 0x24, 0x49, 0x92, 0xa4, 0xaa, 0xaa,
    0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa,
    0xaa, 0xaa, 0x02
  };
  const size_t expected_out_len = sizeof(expected_out);

  EXPECT_TRUE(vtenc_set_encode_u64(in, in_len, out, out_cap, &out_len) == VtencErrorNoError);
  EXPECT_TRUE(out_len == expected_out_len);
  EXPECT_TRUE(memcmp(out, expected_out, expected_out_len) == 0);

  return 1;
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
