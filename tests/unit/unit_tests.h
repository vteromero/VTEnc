/**
  Copyright (c) 2019 Vicente Romero Calero. All rights reserved.
  Licensed under the MIT License.
  See LICENSE file in the project root for full license information.
 */
#ifndef VTENC_UNIT_TESTS_H_
#define VTENC_UNIT_TESTS_H_

#include <stdio.h>

#define EXPECT_TRUE(test)                 \
do {                                      \
  if (!(test)) {                          \
    printf("\n\t\""#test"\" failed!\n");  \
    return 0;                             \
  }                                       \
} while(0)

#define EXPECT_TRUE_MSG(test, msg)                  \
do {                                                \
  if (!(test)) {                                    \
    printf("\n\t\""#test"\" failed: %s\n", (msg));  \
    return 0;                                       \
  }                                                 \
} while(0)

int test_bits_swap_u16(void);
int test_bits_swap_u32(void);
int test_bits_swap_u64(void);

int test_bits_len_u8(void);
int test_bits_len_u16(void);
int test_bits_len_u32(void);
int test_bits_len_u64(void);

int test_little_endian_read_and_write_u16(void);
int test_little_endian_read_and_write_u32(void);
int test_little_endian_read_and_write_u64(void);

int test_bswriter_align_buffer_size(void);
int test_bswriter_init_1(void);
int test_bswriter_init_2(void);
int test_bswriter_write_1(void);
int test_bswriter_write_2(void);
int test_bswriter_write_3(void);
int test_bswriter_close_1(void);
int test_bswriter_close_2(void);

int test_bsreader_init_1(void);
int test_bsreader_init_2(void);
int test_bsreader_read_1(void);
int test_bsreader_read_2(void);
int test_bsreader_read_3(void);
int test_bsreader_read_4(void);
int test_bsreader_read_5(void);
int test_bsreader_read_6(void);
int test_bsreader_size(void);

int test_bclstack_new(void);
int test_bclstack_put_and_get(void);

int test_count_zeros_at_bit_pos8(void);
int test_count_zeros_at_bit_pos16(void);
int test_count_zeros_at_bit_pos32(void);
int test_count_zeros_at_bit_pos64(void);

int test_vtenc_encoder_init(void);

int test_vtenc_encode8(void);
int test_vtenc_encode16(void);
int test_vtenc_encode32(void);
int test_vtenc_encode64(void);

int test_vtenc_max_encoded_size8(void);
int test_vtenc_max_encoded_size16(void);
int test_vtenc_max_encoded_size32(void);
int test_vtenc_max_encoded_size64(void);

int test_vtenc_decoder_init(void);

int test_vtenc_decode8(void);
int test_vtenc_decode16(void);
int test_vtenc_decode32(void);
int test_vtenc_decode64(void);

#endif /* VTENC_UNIT_TESTS_H_ */
