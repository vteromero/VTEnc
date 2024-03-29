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
  EXPECT_TRUE(bswriter_align_buffer_size(1) == 9);
  EXPECT_TRUE(bswriter_align_buffer_size(7) == 15);
  EXPECT_TRUE(bswriter_align_buffer_size(8) == 16);
  EXPECT_TRUE(bswriter_align_buffer_size(9) == 17);
  EXPECT_TRUE(bswriter_align_buffer_size(13) == 21);
  EXPECT_TRUE(bswriter_align_buffer_size(16) == 24);
  EXPECT_TRUE(bswriter_align_buffer_size(33) == 41);
  EXPECT_TRUE(bswriter_align_buffer_size(48) == 56);

  return 1;
}

int test_bswriter_init_1(void)
{
  struct bswriter writer;
  const size_t buf_cap = 4;
  uint8_t buf[buf_cap];

  EXPECT_TRUE(bswriter_init(&writer, buf, buf_cap) == VTENC_ERR_BUFFER_TOO_SMALL);

  return 1;
}

int test_bswriter_init_2(void)
{
  struct bswriter writer;
  const size_t buf_cap = 8;
  uint8_t buf[buf_cap];

  EXPECT_TRUE(bswriter_init(&writer, buf, buf_cap) == VTENC_OK);

  return 1;
}

int test_bswriter_write_1(void)
{
  struct bswriter writer;
  const size_t buf_sz = 10;
  const size_t buf_cap = bswriter_align_buffer_size(buf_sz);
  uint8_t buf[buf_cap];

  EXPECT_TRUE(bswriter_init(&writer, buf, buf_cap) == VTENC_OK);

  bswriter_write(&writer, 0xffff, 16);
  bswriter_write(&writer, 0x2, 4);
  bswriter_write(&writer, 0x2, 4);
  bswriter_write(&writer, 0x00, 8);
  bswriter_write(&writer, 0x99999999, 32);
  bswriter_write(&writer, 0x44, 8);
  bswriter_write(&writer, 0xaa, 8);

  EXPECT_TRUE(memcmp(buf, "\xff\xff\x22\x00\x99\x99\x99\x99\x44\xaa", buf_sz) == 0);

  return 1;
}

int test_bswriter_write_2(void)
{
  struct bswriter writer;
  const size_t buf_sz = 8;
  const size_t buf_cap = bswriter_align_buffer_size(buf_sz);
  uint8_t buf[buf_cap];

  EXPECT_TRUE(bswriter_init(&writer, buf, buf_cap) == VTENC_OK);

  bswriter_write(&writer, 0x0, 0);
  bswriter_write(&writer, 0x0, 0);
  bswriter_write(&writer, 0xffffffff, 32);
  bswriter_write(&writer, 0x7fffffff, 31);
  bswriter_write(&writer, 0x0, 0);
  bswriter_write(&writer, 0x0, 0);
  bswriter_write(&writer, 0x1, 1);

  EXPECT_TRUE(memcmp(buf, "\xff\xff\xff\xff\xff\xff\xff\xff", buf_sz) == 0);

  return 1;
}

int test_bswriter_write_3(void)
{
  struct bswriter writer;
  const size_t buf_sz = 16;
  const size_t buf_cap = bswriter_align_buffer_size(buf_sz);
  uint8_t buf[buf_cap];

  memset(buf, 0, buf_cap);

  EXPECT_TRUE(bswriter_init(&writer, buf, buf_cap) == VTENC_OK);

  bswriter_write(&writer, 0x0, 7);
  bswriter_write(&writer, 0xfffffffffffffe, 56);
  bswriter_write(&writer, 0x1, 1);

  bswriter_write(&writer, 0x7f, 7);
  bswriter_write(&writer, 0x1, 56);
  bswriter_write(&writer, 0x0, 1);

  EXPECT_TRUE(
    memcmp(buf,
      "\x00\xff\xff\xff\xff\xff\xff\xff"
      "\xff\x00\x00\x00\x00\x00\x00\x00", buf_sz) == 0
  );

  return 1;
}

int test_bswriter_append_and_flush(void)
{
  struct bswriter writer;
  const size_t buf_sz = 5;
  const size_t buf_cap = bswriter_align_buffer_size(buf_sz);
  uint8_t buf[buf_cap];

  EXPECT_TRUE(bswriter_init(&writer, buf, buf_cap) == VTENC_OK);

  bswriter_append(&writer, 0xffff, 16);
  bswriter_append(&writer, 0x55, 8);
  bswriter_append(&writer, 0xabab, 16);

  bswriter_flush(&writer);

  EXPECT_TRUE(memcmp(buf, "\xff\xff\x55\xab\xab", buf_sz) == 0);

  return 1;
}

int test_bswriter_append_fast_and_flush(void)
{
  struct bswriter writer;
  const size_t buf_sz = 5;
  const size_t buf_cap = bswriter_align_buffer_size(buf_sz);
  uint8_t buf[buf_cap];

  EXPECT_TRUE(bswriter_init(&writer, buf, buf_cap) == VTENC_OK);

  bswriter_append_fast(&writer, 0xffff, 16);
  bswriter_append_fast(&writer, 0x55, 8);
  bswriter_append_fast(&writer, 0xabab, 16);

  bswriter_flush(&writer);

  EXPECT_TRUE(memcmp(buf, "\xff\xff\x55\xab\xab", buf_sz) == 0);

  return 1;
}

int test_bswriter_size_1(void)
{
  struct bswriter writer;
  const size_t buf_sz = 8;
  const size_t buf_cap = bswriter_align_buffer_size(buf_sz);
  uint8_t buf[buf_cap];

  EXPECT_TRUE(bswriter_init(&writer, buf, buf_cap) == VTENC_OK);
  EXPECT_TRUE(bswriter_size(&writer) == 0);

  return 1;
}

int test_bswriter_size_2(void)
{
  struct bswriter writer;
  const size_t buf_sz = 8;
  const size_t buf_cap = bswriter_align_buffer_size(buf_sz);
  uint8_t buf[buf_cap];

  EXPECT_TRUE(bswriter_init(&writer, buf, buf_cap) == VTENC_OK);

  bswriter_write(&writer, 0x12, 8);
  bswriter_write(&writer, 0x3, 2);
  bswriter_write(&writer, 0x7, 3);
  bswriter_write(&writer, 0xe, 4);

  EXPECT_TRUE(bswriter_size(&writer) == 3);

  return 1;
}

int test_bsreader_read_1(void)
{
  struct bsreader reader;
  const uint8_t buf[] = {0xff, 0x66};
  const size_t buf_len = sizeof(buf);

  bsreader_init(&reader, buf, buf_len);

  EXPECT_TRUE(bsreader_read(&reader, 8) == 0xff);
  EXPECT_TRUE(bsreader_read(&reader, 8) == 0x66);

  return 1;
}

int test_bsreader_read_2(void)
{
  struct bsreader reader;
  const uint8_t buf[] = {0xba};
  const size_t buf_len = sizeof(buf);

  bsreader_init(&reader, buf, buf_len);

  bsreader_read(&reader, 0);
  EXPECT_TRUE(bsreader_read(&reader, 4) == 0xa);

  bsreader_read(&reader, 0);
  EXPECT_TRUE(bsreader_read(&reader, 4) == 0xb);

  return 1;
}

int test_bsreader_read_3(void)
{
  struct bsreader reader;
  const uint8_t buf[] = {
    0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22,
    0x33, 0x33, 0x33, 0x33, 0x33, 0x33
  };
  const size_t buf_len = sizeof(buf);

  bsreader_init(&reader, buf, buf_len);

  EXPECT_TRUE(bsreader_read(&reader, 48) == 0x111111111111);
  EXPECT_TRUE(bsreader_read(&reader, 48) == 0x222222222222);
  EXPECT_TRUE(bsreader_read(&reader, 48) == 0x333333333333);

  return 1;
}

int test_bsreader_read_4(void)
{
  struct bsreader reader;
  const uint8_t buf[] = {
    0xff, 0xab, 0x11, 0xcd, 0x55, 0x55, 0x55, 0x55, 0x66, 0x66, 0x66, 0x66
  };
  const size_t buf_len = sizeof(buf);

  bsreader_init(&reader, buf, buf_len);

  EXPECT_TRUE(bsreader_read(&reader, 8) == 0xff);
  EXPECT_TRUE(bsreader_read(&reader, 4) == 0xb);
  EXPECT_TRUE(bsreader_read(&reader, 4) == 0xa);
  EXPECT_TRUE(bsreader_read(&reader, 1) == 0x1);
  EXPECT_TRUE(bsreader_read(&reader, 2) == 0x0);
  EXPECT_TRUE(bsreader_read(&reader, 2) == 0x2);
  EXPECT_TRUE(bsreader_read(&reader, 3) == 0x0);
  EXPECT_TRUE(bsreader_read(&reader, 8) == 0xcd);
  EXPECT_TRUE(bsreader_read(&reader, 16) == 0x5555);
  EXPECT_TRUE(bsreader_read(&reader, 16) == 0x5555);
  EXPECT_TRUE(bsreader_read(&reader, 32) == 0x66666666);

  return 1;
}

int test_bsreader_read_5(void)
{
  struct bsreader reader;
  const uint8_t buf[] = {
    0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55,
    0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55
  };
  const size_t buf_len = sizeof(buf);

  bsreader_init(&reader, buf, buf_len);

  EXPECT_TRUE(bsreader_read(&reader, 7) == 0x55);
  EXPECT_TRUE(bsreader_read(&reader, 56) == 0xaaaaaaaaaaaaaa);
  EXPECT_TRUE(bsreader_read(&reader, 1) == 0x0);

  EXPECT_TRUE(bsreader_read(&reader, 56) == 0x55555555555555);
  EXPECT_TRUE(bsreader_read(&reader, 8) == 0x55);

  return 1;
}

int test_bsreader_size(void)
{
  struct bsreader reader;
  const uint8_t buf[] = {
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff
  };
  const size_t buf_len = sizeof(buf);

  bsreader_init(&reader, buf, buf_len);

  EXPECT_TRUE(bsreader_size(&reader) == 0);
  bsreader_read(&reader, 1); EXPECT_TRUE(bsreader_size(&reader) == 1);
  bsreader_read(&reader, 5); EXPECT_TRUE(bsreader_size(&reader) == 1);
  bsreader_read(&reader, 5); EXPECT_TRUE(bsreader_size(&reader) == 2);
  bsreader_read(&reader, 5); EXPECT_TRUE(bsreader_size(&reader) == 2);
  bsreader_read(&reader, 1); EXPECT_TRUE(bsreader_size(&reader) == 3);
  bsreader_read(&reader, 20); EXPECT_TRUE(bsreader_size(&reader) == 5);
  bsreader_read(&reader, 40); EXPECT_TRUE(bsreader_size(&reader) == 10);
  bsreader_read(&reader, 16); EXPECT_TRUE(bsreader_size(&reader) == 12);

  return 1;
}
