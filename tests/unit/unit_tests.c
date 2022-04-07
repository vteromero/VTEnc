/**
  Copyright (c) 2019 Vicente Romero Calero. All rights reserved.
  Licensed under the MIT License.
  See LICENSE file in the project root for full license information.
 */
#include "unit_tests.h"

#include <stdio.h>

#define RUN_TEST(fn_name)           \
do {                                \
  printf(""#fn_name"...");          \
  if ((fn_name)()) printf(" OK\n"); \
  else {                            \
    printf(" KO\n");                \
    return 1;                       \
  }                                 \
} while (0)

int main()
{
  RUN_TEST(test_bits_swap_u16);
  RUN_TEST(test_bits_swap_u32);
  RUN_TEST(test_bits_swap_u64);

  RUN_TEST(test_bits_len_u8);
  RUN_TEST(test_bits_len_u16);
  RUN_TEST(test_bits_len_u32);
  RUN_TEST(test_bits_len_u64);

  RUN_TEST(test_little_endian_read_and_write_u16);
  RUN_TEST(test_little_endian_read_and_write_u32);
  RUN_TEST(test_little_endian_read_and_write_u64);

  RUN_TEST(test_bswriter_align_buffer_size);
  RUN_TEST(test_bswriter_init_1);
  RUN_TEST(test_bswriter_init_2);
  RUN_TEST(test_bswriter_write_1);
  RUN_TEST(test_bswriter_write_2);
  RUN_TEST(test_bswriter_write_3);
  RUN_TEST(test_bswriter_append_and_flush);
  RUN_TEST(test_bswriter_size_1);
  RUN_TEST(test_bswriter_size_2);

  RUN_TEST(test_bsreader_read_1);
  RUN_TEST(test_bsreader_read_2);
  RUN_TEST(test_bsreader_read_3);
  RUN_TEST(test_bsreader_read_4);
  RUN_TEST(test_bsreader_read_5);
  RUN_TEST(test_bsreader_read_6);
  RUN_TEST(test_bsreader_read_7);
  RUN_TEST(test_bsreader_size);

  RUN_TEST(test_stack_init);
  RUN_TEST(test_stack_push_and_pop);

  RUN_TEST(test_count_zeros_at_bit_pos8);
  RUN_TEST(test_count_zeros_at_bit_pos16);
  RUN_TEST(test_count_zeros_at_bit_pos32);
  RUN_TEST(test_count_zeros_at_bit_pos64);

  RUN_TEST(test_vtenc_encode8);
  RUN_TEST(test_vtenc_encode16);
  RUN_TEST(test_vtenc_encode32);
  RUN_TEST(test_vtenc_encode64);

  RUN_TEST(test_vtenc_max_encoded_size8);
  RUN_TEST(test_vtenc_max_encoded_size16);
  RUN_TEST(test_vtenc_max_encoded_size32);
  RUN_TEST(test_vtenc_max_encoded_size64);

  RUN_TEST(test_vtenc_decode8);
  RUN_TEST(test_vtenc_decode16);
  RUN_TEST(test_vtenc_decode32);
  RUN_TEST(test_vtenc_decode64);

  return 0;
}
