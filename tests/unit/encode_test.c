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
    0x0b, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 0x8d, 0x65, 0xab, 0x8e,
    0xd6, 0x42, 0x4e, 0xa8, 0x00
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
    0x09, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0e, 0x51, 0x1d, 0x08, 0x00,
    0xc0, 0x03
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
    0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xda, 0xa3, 0xb3, 0x4a, 0x8c,
    0xae, 0x8d, 0x3f, 0x17, 0x34, 0xbb, 0x8c, 0x5b, 0x00
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
    0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0xa7, 0x2d, 0x8a, 0x02,
    0x6d, 0xf1, 0x33, 0xf3, 0x0c
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
    0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xca, 0xd2, 0x0d, 0xd6, 0x97,
    0xfb, 0x8d, 0xbe, 0xa7, 0xad, 0x8f, 0xf6, 0x5c, 0x73, 0x88, 0x4e, 0xfd,
    0xaf, 0xb1, 0x01
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
    0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x6c, 0x53, 0x11, 0x54, 0x50,
    0x11, 0x55, 0x41, 0x90, 0x20, 0x41, 0x90, 0x20, 0x49, 0x90, 0x04, 0x40,
    0x10, 0x20, 0x00
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
    0x24, 0xc9, 0xbd, 0x2d, 0x47, 0x1c, 0x53, 0xd5, 0xff, 0xff, 0xff, 0x05,
    0xe8, 0x49, 0x8b, 0xa8, 0xaa, 0x5d, 0x89, 0xe0, 0xff, 0xb7, 0x9a
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
    0x6d, 0xdb, 0x4e, 0x45, 0x45, 0x45, 0x45, 0x45, 0x45, 0x45, 0x45, 0x45,
    0x45, 0xe5, 0xff, 0xff, 0x7f, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66,
    0x06
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
  const uint8_t expected_out[] = {0x0b, 0x48, 0x90, 0x44, 0x44, 0x04};
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
  const uint8_t expected_out[] = {0x05, 0xac, 0xae, 0x72, 0xd4, 0x34, 0x01};
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
    0x07, 0x00, 0x96, 0x2b, 0xfa, 0xe3, 0x11, 0x02, 0xfb, 0x1a, 0x77, 0x7b,
    0xfd, 0x87, 0x34, 0xc0, 0x08
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
    0x0b, 0x00, 0x8c, 0x24, 0x00, 0x92, 0x20, 0x09, 0x80, 0x00, 0x08, 0x08,
    0x80
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
    0x04, 0x00, 0x00, 0x00, 0x6c, 0x7f, 0xbe, 0x89, 0x8c, 0x60, 0x56, 0x71,
    0x50, 0x38, 0x32, 0xc2, 0xb7, 0x0b, 0x2a, 0xd2, 0x6f, 0x2e, 0xfb, 0x0d
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
    0x0d, 0x00, 0x00, 0x00, 0xee, 0xee, 0xee, 0xee, 0x06, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x88, 0x88, 0x48, 0x45, 0x40, 0x40, 0x50, 0x55,
    0x49, 0x92, 0x04, 0x41, 0x82, 0x20, 0x49, 0x12
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
    0xff, 0x1b, 0x80, 0x08, 0x80, 0x08, 0x80, 0x98, 0xb9, 0x47, 0x64, 0x56,
    0x75, 0xb7, 0x6d, 0x5b, 0xe2, 0xe1, 0xe1, 0xe1, 0xe1, 0x57, 0x55, 0x55,
    0x55, 0x55, 0xed, 0xdf, 0xdf, 0xdf, 0xdf, 0xab, 0x56, 0x15, 0x61, 0x26,
    0xda, 0xed, 0xce, 0x74, 0x03
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
    0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x4d, 0x55, 0x55, 0x55,
    0x55, 0x55, 0x55, 0x55, 0x55, 0xd5, 0xb6, 0x4d, 0x55, 0x55, 0x55, 0x55,
    0x55, 0x55, 0x55, 0x25, 0x48, 0x92, 0x24, 0x49, 0x92, 0x24, 0x49, 0x92,
    0x24, 0x49, 0x02
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
