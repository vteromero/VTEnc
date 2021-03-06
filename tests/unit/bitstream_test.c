/**
  Copyright (c) 2019 Vicente Romero Calero. All rights reserved.
  Licensed under the MIT License.
  See LICENSE file in the project root for full license information.
 */
#include <stdlib.h>
#include <string.h>

#include "unit_tests.h"
#include "../../bitstream.h"

int test_bswriter_align_buffer_size(void)
{
  EXPECT_TRUE(bswriter_align_buffer_size(0) == 8);
  EXPECT_TRUE(bswriter_align_buffer_size(1) == 8);
  EXPECT_TRUE(bswriter_align_buffer_size(7) == 8);
  EXPECT_TRUE(bswriter_align_buffer_size(8) == 8);
  EXPECT_TRUE(bswriter_align_buffer_size(9) == 16);
  EXPECT_TRUE(bswriter_align_buffer_size(13) == 16);
  EXPECT_TRUE(bswriter_align_buffer_size(16) == 16);
  EXPECT_TRUE(bswriter_align_buffer_size(33) == 40);
  EXPECT_TRUE(bswriter_align_buffer_size(48) == 48);

  return 1;
}

int test_bswriter_init_1(void)
{
  struct BSWriter writer;
  const size_t buf_cap = 4;
  uint8_t buf[buf_cap];

  EXPECT_TRUE(bswriter_init(&writer, buf, buf_cap) == VtencErrorBufferTooSmall);

  return 1;
}

int test_bswriter_init_2(void)
{
  struct BSWriter writer;
  const size_t buf_cap = 8;
  uint8_t buf[buf_cap];

  EXPECT_TRUE(bswriter_init(&writer, buf, buf_cap) == VtencErrorNoError);

  return 1;
}

int test_bswriter_write_1(void)
{
  struct BSWriter writer;
  const size_t buf_cap = 16;
  uint8_t buf[buf_cap];

  memset(buf, 0, buf_cap);

  EXPECT_TRUE(bswriter_init(&writer, buf, buf_cap) == VtencErrorNoError);

  EXPECT_TRUE(bswriter_write(&writer, 0xffff, 16) == VtencErrorNoError);
  EXPECT_TRUE(bswriter_write(&writer, 0x2, 4) == VtencErrorNoError);
  EXPECT_TRUE(bswriter_write(&writer, 0x2, 4) == VtencErrorNoError);
  EXPECT_TRUE(bswriter_write(&writer, 0x00, 8) == VtencErrorNoError);
  EXPECT_TRUE(bswriter_write(&writer, 0x99999999, 32) == VtencErrorNoError);
  EXPECT_TRUE(bswriter_write(&writer, 0x44, 8) == VtencErrorNoError);
  EXPECT_TRUE(bswriter_write(&writer, 0xaa, 8) == VtencErrorNoError);

  bswriter_close(&writer);

  EXPECT_TRUE(memcmp(buf, "\xff\xff\x22\x00\x99\x99\x99\x99\x44\xaa\x00\x00\x00\x00\x00\x00", buf_cap) == 0);

  return 1;
}

int test_bswriter_write_2(void)
{
  struct BSWriter writer;
  const size_t buf_cap = 8;
  uint8_t buf[buf_cap];

  memset(buf, 0, buf_cap);

  EXPECT_TRUE(bswriter_init(&writer, buf, buf_cap) == VtencErrorNoError);

  EXPECT_TRUE(bswriter_write(&writer, 0x0, 0) == VtencErrorNoError);
  EXPECT_TRUE(bswriter_write(&writer, 0x0, 0) == VtencErrorNoError);
  EXPECT_TRUE(bswriter_write(&writer, 0xffffffff, 32) == VtencErrorNoError);
  EXPECT_TRUE(bswriter_write(&writer, 0x7fffffff, 31) == VtencErrorNoError);
  EXPECT_TRUE(bswriter_write(&writer, 0x0, 0) == VtencErrorNoError);
  EXPECT_TRUE(bswriter_write(&writer, 0x0, 0) == VtencErrorNoError);
  EXPECT_TRUE(bswriter_write(&writer, 0x1, 1) == VtencErrorEndOfStream);
  EXPECT_TRUE(bswriter_write(&writer, 0x1, 1) == VtencErrorEndOfStream);

  bswriter_close(&writer);

  EXPECT_TRUE(memcmp(buf, "\xff\xff\xff\xff\xff\xff\xff\x7f", buf_cap) == 0);

  return 1;
}

int test_bswriter_write_3(void)
{
  struct BSWriter writer;
  const size_t buf_cap = 24;
  uint8_t buf[buf_cap];

  memset(buf, 0, buf_cap);

  EXPECT_TRUE(bswriter_init(&writer, buf, buf_cap) == VtencErrorNoError);

  EXPECT_TRUE(bswriter_write(&writer, 0x1ffffffffffffff, 57) == VtencErrorNoError);
  EXPECT_TRUE(bswriter_write(&writer, 0x1ffffffffffffff, 57) == VtencErrorNoError);
  EXPECT_TRUE(bswriter_write(&writer, 0x1ffffffffffffff, 57) == VtencErrorNoError);

  bswriter_close(&writer);

  EXPECT_TRUE(memcmp(buf,
    "\xff\xff\xff\xff\xff\xff\xff\xff"
    "\xff\xff\xff\xff\xff\xff\xff\xff"
    "\xff\xff\xff\xff\xff\x07\x00\x00", buf_cap) == 0);

  return 1;
}

int test_bswriter_close_1(void)
{
  struct BSWriter writer;
  const size_t buf_cap = 8;
  uint8_t buf[buf_cap];

  EXPECT_TRUE(bswriter_init(&writer, buf, buf_cap) == VtencErrorNoError);
  EXPECT_TRUE(bswriter_close(&writer) == 0);

  return 1;
}

int test_bswriter_close_2(void)
{
  struct BSWriter writer;
  const size_t buf_cap = 8;
  uint8_t buf[buf_cap];

  EXPECT_TRUE(bswriter_init(&writer, buf, buf_cap) == VtencErrorNoError);

  EXPECT_TRUE(bswriter_write(&writer, 0x12, 8) == VtencErrorNoError);
  EXPECT_TRUE(bswriter_write(&writer, 0x3, 2) == VtencErrorNoError);
  EXPECT_TRUE(bswriter_write(&writer, 0x7, 3) == VtencErrorNoError);
  EXPECT_TRUE(bswriter_write(&writer, 0xe, 4) == VtencErrorNoError);

  EXPECT_TRUE(bswriter_close(&writer) == 3);

  return 1;
}

int test_bsreader_read_1(void)
{
  struct BSReader reader;
  const uint8_t buf[] = {};
  const size_t buf_len = sizeof(buf);
  uint64_t val=0;

  bsreader_init(&reader, buf, buf_len);

  EXPECT_TRUE(bsreader_read(&reader, 8, &val) == VtencErrorEndOfStream);

  return 1;
}

int test_bsreader_read_2(void)
{
  struct BSReader reader;
  const uint8_t buf[] = {0xff};
  const size_t buf_len = sizeof(buf);
  uint64_t val=0;

  bsreader_init(&reader, buf, buf_len);

  EXPECT_TRUE(bsreader_read(&reader, 8, &val) == VtencErrorNoError && val == 0xff);
  EXPECT_TRUE(bsreader_read(&reader, 8, &val) == VtencErrorEndOfStream);

  return 1;
}

int test_bsreader_read_3(void)
{
  struct BSReader reader;
  const uint8_t buf[] = {0xff, 0x66};
  const size_t buf_len = sizeof(buf);
  uint64_t val=0;

  bsreader_init(&reader, buf, buf_len);

  EXPECT_TRUE(bsreader_read(&reader, 8, &val) == VtencErrorNoError && val == 0xff);
  EXPECT_TRUE(bsreader_read(&reader, 16, &val) == VtencErrorNotEnoughBits);
  EXPECT_TRUE(bsreader_read(&reader, 8, &val) == VtencErrorNoError && val == 0x66);

  return 1;
}

int test_bsreader_read_4(void)
{
  struct BSReader reader;
  const uint8_t buf[] = {0xba};
  const size_t buf_len = sizeof(buf);
  uint64_t val=0;

  bsreader_init(&reader, buf, buf_len);

  EXPECT_TRUE(bsreader_read(&reader, 0, &val) == VtencErrorNoError);
  EXPECT_TRUE(bsreader_read(&reader, 4, &val) == VtencErrorNoError && val == 0xa);
  EXPECT_TRUE(bsreader_read(&reader, 0, &val) == VtencErrorNoError);
  EXPECT_TRUE(bsreader_read(&reader, 4, &val) == VtencErrorNoError && val == 0xb);
  EXPECT_TRUE(bsreader_read(&reader, 0, &val) == VtencErrorNoError);
  EXPECT_TRUE(bsreader_read(&reader, 1, &val) == VtencErrorEndOfStream);

  return 1;
}

int test_bsreader_read_5(void)
{
  struct BSReader reader;
  const uint8_t buf[] = {
    0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22,
    0x33, 0x33, 0x33, 0x33, 0x33, 0x33
  };
  const size_t buf_len = sizeof(buf);
  uint64_t val=0;

  bsreader_init(&reader, buf, buf_len);

  EXPECT_TRUE(bsreader_read(&reader, 48, &val) == VtencErrorNoError && val == 0x111111111111);
  EXPECT_TRUE(bsreader_read(&reader, 48, &val) == VtencErrorNoError && val == 0x222222222222);
  EXPECT_TRUE(bsreader_read(&reader, 48, &val) == VtencErrorNoError && val == 0x333333333333);
  EXPECT_TRUE(bsreader_read(&reader, 8, &val) == VtencErrorEndOfStream);

  return 1;
}

int test_bsreader_read_6(void)
{
  struct BSReader reader;
  const uint8_t buf[] = {
    0xff, 0xab, 0x11, 0xcd, 0x55, 0x55, 0x55, 0x55, 0x66, 0x66, 0x66, 0x66
  };
  const size_t buf_len = sizeof(buf);
  uint64_t val=0;

  bsreader_init(&reader, buf, buf_len);

  EXPECT_TRUE(bsreader_read(&reader, 8, &val) == VtencErrorNoError && val == 0xff);
  EXPECT_TRUE(bsreader_read(&reader, 4, &val) == VtencErrorNoError && val == 0xb);
  EXPECT_TRUE(bsreader_read(&reader, 4, &val) == VtencErrorNoError && val == 0xa);
  EXPECT_TRUE(bsreader_read(&reader, 1, &val) == VtencErrorNoError && val == 0x1);
  EXPECT_TRUE(bsreader_read(&reader, 2, &val) == VtencErrorNoError && val == 0x0);
  EXPECT_TRUE(bsreader_read(&reader, 2, &val) == VtencErrorNoError && val == 0x2);
  EXPECT_TRUE(bsreader_read(&reader, 3, &val) == VtencErrorNoError && val == 0x0);
  EXPECT_TRUE(bsreader_read(&reader, 8, &val) == VtencErrorNoError && val == 0xcd);
  EXPECT_TRUE(bsreader_read(&reader, 16, &val) == VtencErrorNoError && val == 0x5555);
  EXPECT_TRUE(bsreader_read(&reader, 16, &val) == VtencErrorNoError && val == 0x5555);
  EXPECT_TRUE(bsreader_read(&reader, 32, &val) == VtencErrorNoError && val == 0x66666666);
  EXPECT_TRUE(bsreader_read(&reader, 8, &val) == VtencErrorEndOfStream);

  return 1;
}

int test_bsreader_read_7(void)
{
  struct BSReader reader;
  const uint8_t buf[] = {
    0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55,
    0x55, 0x55, 0x55
  };
  const size_t buf_len = sizeof(buf);
  uint64_t val=0;

  bsreader_init(&reader, buf, buf_len);

  EXPECT_TRUE(bsreader_read(&reader, 57, &val) == VtencErrorNoError && val == 0x155555555555555);
  EXPECT_TRUE(bsreader_read(&reader, 57, &val) == VtencErrorNoError && val == 0x0aaaaaaaaaaaaaa);
  EXPECT_TRUE(bsreader_read(&reader, 6, &val) == VtencErrorNoError && val == 0x15);

  return 1;
}

int test_bsreader_size(void)
{
  struct BSReader reader;
  const uint8_t buf[] = {
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff
  };
  const size_t buf_len = sizeof(buf);
  uint64_t val=0;

  bsreader_init(&reader, buf, buf_len);

  EXPECT_TRUE(bsreader_size(&reader) == 0);
  bsreader_read(&reader, 1, &val); EXPECT_TRUE(bsreader_size(&reader) == 1);
  bsreader_read(&reader, 5, &val); EXPECT_TRUE(bsreader_size(&reader) == 1);
  bsreader_read(&reader, 5, &val); EXPECT_TRUE(bsreader_size(&reader) == 2);
  bsreader_read(&reader, 5, &val); EXPECT_TRUE(bsreader_size(&reader) == 2);
  bsreader_read(&reader, 1, &val); EXPECT_TRUE(bsreader_size(&reader) == 3);
  bsreader_read(&reader, 20, &val); EXPECT_TRUE(bsreader_size(&reader) == 5);
  bsreader_read(&reader, 40, &val); EXPECT_TRUE(bsreader_size(&reader) == 10);
  bsreader_read(&reader, 16, &val); EXPECT_TRUE(bsreader_size(&reader) == 12);

  return 1;
}
