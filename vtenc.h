/**
  Copyright (c) 2019 Vicente Romero Calero. All rights reserved.
  Licensed under the MIT License.
  See LICENSE file in the project root for full license information.
 */
#ifndef VTENC_H_
#define VTENC_H_

#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * This library provides a series of functions to encode and decode sorted
 * sequences of unsigned integers using VTEnc algorithm. It supports different
 * types (uint8_t, uint16_t, uint32_t and uint64_t) and two different kind of
 * sequences: lists and sets.
 *
 * Lists and sets differ in that lists can have duplicate values, whereas sets
 * cannot. Both have to be sorted in ascending order.
 */

/* Error codes */
typedef enum {
  VtencErrorNoError         = 0,
  VtencErrorMemoryAlloc     = 1,
  VtencErrorBufferTooSmall  = 2,
  VtencErrorEndOfStream     = 3,
  VtencErrorNotEnoughBits   = 4,
  VtencErrorInputTooSmall   = 5,
  VtencErrorInputTooBig     = 6,
  VtencErrorWrongFormat     = 7
} VtencErrorCode;

/**
 * Encoding functions.
 *
 * Each function encodes the list or set `in` into the already-allocated stream
 * of bytes `out`.
 *
 * `in_len`: size of `in`.
 * `out_cap`: capacity in bytes of `out`.
 * `out_len`: actual size of the encoded output. This is an output argument, so
 *    its value will be available after the encode function is called.
 *
 * Returns 'VtencErrorNoError' if there was no error. Otherwise, a specific error
 * code is returned.
 *
 * Note that these functions assume that `in` is a sorted sequence and they don't
 * check its order. If you pass in an unsorted list or set, they'll still
 * return a 'VtencErrorNoError' code, but the output won't correspond to the
 * correct encoded stream for the input sequence.
 */
VtencErrorCode vtenc_list_encode_u8(const uint8_t *in, size_t in_len, uint8_t *out, size_t out_cap, size_t *out_len);
VtencErrorCode vtenc_list_encode_u16(const uint16_t *in, size_t in_len, uint8_t *out, size_t out_cap, size_t *out_len);
VtencErrorCode vtenc_list_encode_u32(const uint32_t *in, size_t in_len, uint8_t *out, size_t out_cap, size_t *out_len);
VtencErrorCode vtenc_list_encode_u64(const uint64_t *in, size_t in_len, uint8_t *out, size_t out_cap, size_t *out_len);

VtencErrorCode vtenc_set_encode_u8(const uint8_t *in, size_t in_len, uint8_t *out, size_t out_cap, size_t *out_len);
VtencErrorCode vtenc_set_encode_u16(const uint16_t *in, size_t in_len, uint8_t *out, size_t out_cap, size_t *out_len);
VtencErrorCode vtenc_set_encode_u32(const uint32_t *in, size_t in_len, uint8_t *out, size_t out_cap, size_t *out_len);
VtencErrorCode vtenc_set_encode_u64(const uint64_t *in, size_t in_len, uint8_t *out, size_t out_cap, size_t *out_len);

typedef struct {
  int has_repeated_values;
  int skip_full_subtrees;
  VtencErrorCode last_error_code;
} VtencEncoder;

void vtenc_encoder_init(VtencEncoder *enc);

size_t vtenc_encode8(VtencEncoder *enc, const uint8_t *in, size_t in_len, uint8_t *out, size_t out_cap);
size_t vtenc_encode16(VtencEncoder *enc, const uint16_t *in, size_t in_len, uint8_t *out, size_t out_cap);
size_t vtenc_encode32(VtencEncoder *enc, const uint32_t *in, size_t in_len, uint8_t *out, size_t out_cap);
size_t vtenc_encode64(VtencEncoder *enc, const uint64_t *in, size_t in_len, uint8_t *out, size_t out_cap);

/**
 * Functions to calculate the maximum encoded size in bytes when encoding a list
 * or set of size `in_len`. The returned value is an approximation of the actual
 * encoded length and it's guaranteed to be at least as big as the actual size.
 */
size_t vtenc_list_max_encoded_size_u8(size_t in_len);
size_t vtenc_list_max_encoded_size_u16(size_t in_len);
size_t vtenc_list_max_encoded_size_u32(size_t in_len);
size_t vtenc_list_max_encoded_size_u64(size_t in_len);

size_t vtenc_set_max_encoded_size_u8(size_t in_len);
size_t vtenc_set_max_encoded_size_u16(size_t in_len);
size_t vtenc_set_max_encoded_size_u32(size_t in_len);
size_t vtenc_set_max_encoded_size_u64(size_t in_len);

size_t vtenc_max_encoded_size8(const VtencEncoder *enc, size_t in_len);
size_t vtenc_max_encoded_size16(const VtencEncoder *enc, size_t in_len);
size_t vtenc_max_encoded_size32(const VtencEncoder *enc, size_t in_len);
size_t vtenc_max_encoded_size64(const VtencEncoder *enc, size_t in_len);

/**
 * Decoding functions.
 *
 * Each function decodes the stream of bytes `in` into the already-allocated
 * list or set `out`.
 *
 * `in_len`: size of `in`.
 * `out_len`: size of `out`.
 *
 * Returns 'VtencErrorNoError' in case of success. Otherwise, a specific error
 * code is returned.
 */
VtencErrorCode vtenc_list_decode_u8(const uint8_t *in, size_t in_len, uint8_t *out, size_t out_len);
VtencErrorCode vtenc_list_decode_u16(const uint8_t *in, size_t in_len, uint16_t *out, size_t out_len);
VtencErrorCode vtenc_list_decode_u32(const uint8_t *in, size_t in_len, uint32_t *out, size_t out_len);
VtencErrorCode vtenc_list_decode_u64(const uint8_t *in, size_t in_len, uint64_t *out, size_t out_len);

VtencErrorCode vtenc_set_decode_u8(const uint8_t *in, size_t in_len, uint8_t *out, size_t out_len);
VtencErrorCode vtenc_set_decode_u16(const uint8_t *in, size_t in_len, uint16_t *out, size_t out_len);
VtencErrorCode vtenc_set_decode_u32(const uint8_t *in, size_t in_len, uint32_t *out, size_t out_len);
VtencErrorCode vtenc_set_decode_u64(const uint8_t *in, size_t in_len, uint64_t *out, size_t out_len);

typedef struct {
  int has_repeated_values;
  int skip_full_subtrees;
  VtencErrorCode last_error_code;
} VtencDecoder;

void vtenc_decoder_init(VtencDecoder *dec);

void vtenc_decode8(VtencDecoder *dec, const uint8_t *in, size_t in_len, uint8_t *out, size_t out_len);
void vtenc_decode16(VtencDecoder *dec, const uint8_t *in, size_t in_len, uint16_t *out, size_t out_len);
void vtenc_decode32(VtencDecoder *dec, const uint8_t *in, size_t in_len, uint32_t *out, size_t out_len);
void vtenc_decode64(VtencDecoder *dec, const uint8_t *in, size_t in_len, uint64_t *out, size_t out_len);

/**
 * Functions to extract the size of the decoded sequence from the encoded stream
 * of bytes `in` of size `in_len`. These functions are used to allocate memory
 * for the list or set to be decoded before calling the corresponding decode
 * function.
 */
size_t vtenc_list_decoded_size_u8(const uint8_t *in, size_t in_len);
size_t vtenc_list_decoded_size_u16(const uint8_t *in, size_t in_len);
size_t vtenc_list_decoded_size_u32(const uint8_t *in, size_t in_len);
size_t vtenc_list_decoded_size_u64(const uint8_t *in, size_t in_len);

size_t vtenc_set_decoded_size_u8(const uint8_t *in, size_t in_len);
size_t vtenc_set_decoded_size_u16(const uint8_t *in, size_t in_len);
size_t vtenc_set_decoded_size_u32(const uint8_t *in, size_t in_len);
size_t vtenc_set_decoded_size_u64(const uint8_t *in, size_t in_len);

size_t vtenc_decoded_size8(VtencDecoder *dec, const uint8_t *in, size_t in_len);
size_t vtenc_decoded_size16(VtencDecoder *dec, const uint8_t *in, size_t in_len);
size_t vtenc_decoded_size32(VtencDecoder *dec, const uint8_t *in, size_t in_len);
size_t vtenc_decoded_size64(VtencDecoder *dec, const uint8_t *in, size_t in_len);

#ifdef __cplusplus
}
#endif

#endif /* VTENC_H_ */
