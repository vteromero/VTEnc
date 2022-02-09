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

/*
 * This library provides a series of functions to encode and decode sorted
 * sequences of unsigned integers using VTEnc algorithm.
 *
 * It supports sequences of 4 different types: uint8_t, uint16_t, uint32_t and
 * uint64_t.
 */

/*
 * Result codes.
 *
 * Most VTEnc functions return an integer result code from the following set
 * to indicate success or failure.
 */
#define VTENC_OK                    0     /* Successful code */
#define VTENC_ERR_BUFFER_TOO_SMALL  (-1)  /* Buffer too small */
#define VTENC_ERR_END_OF_STREAM     (-2)  /* Write or Read reaches end of the stream */
#define VTENC_ERR_NOT_ENOUGH_BITS   (-3)  /* Not enough bits to read */
#define VTENC_ERR_INPUT_TOO_BIG     (-4)  /* Input size too big */
#define VTENC_ERR_OUTPUT_TOO_BIG    (-5)  /* Output size too big */
#define VTENC_ERR_WRONG_FORMAT      (-6)  /* Wrong encoded format */

/* Encoding/decoding handler */
typedef struct vtenc vtenc;

/* Initialises the encoding/decoding handler */
int vtenc_init(vtenc *handler);

/* Error codes */
typedef enum {
  VtencErrorNoError         = 0,
  VtencErrorMemoryAlloc     = 1,
  VtencErrorBufferTooSmall  = 2,
  VtencErrorEndOfStream     = 3,
  VtencErrorNotEnoughBits   = 4,
  VtencErrorInputTooBig     = 6,
  VtencErrorOutputTooBig    = 7,
  VtencErrorWrongFormat     = 8
} VtencErrorCode;

/**
 * typedef VtencEncoder - VTEnc encoder.
 */
typedef struct {
  /**
   * Indicates whether repeated values are allowed or not.
   */
  int allow_repeated_values;

  /**
   * Indicates whether to skip full subtrees or not.
   * This parameter is only applicable to sets, i.e. sequences with no repeated
   * values. It's ignored if `allow_repeated_values` is set to 1.
   */
  int skip_full_subtrees;

  /**
   * Minimum cluster length to serialise.
   */
  size_t min_cluster_length;

  /**
   * 'Returning state' after calling a encode function. It'll hold the error
   * code value if the encode function fails, or a 'VtencErrorNoError' value if
   * the function runs successfully.
   */
  VtencErrorCode last_error_code;
} VtencEncoder;

/**
 * vtenc_encoder_init - initialises encoder @enc.
 */
void vtenc_encoder_init(VtencEncoder *enc);

/**
 * vtenc_encode* functions.
 *
 * Functions to encode the sequence @in into the already-allocated stream of
 * bytes @out, using the VTEnc algorithm with the provided encoding parameters.
 *
 * @enc: encoder. Provides encoding parameters and holds the returning state.
 * @in: input sequence to be encoded.
 * @in_len: size of @in.
 * @out: output stream of bytes.
 * @out_cap: capacity of @out / number of allocated bytes in @out.
 *
 * In case of error, @enc->last_error_code contains a specific error code
 * after calling the function. Otherwise, it has a 'VtencErrorNoError' code.
 *
 * Note that these functions assume that @in is a sorted sequence and they don't
 * check its order. If you pass in an unsorted sequence, @enc->last_error_code
 * will still have a 'VtencErrorNoError' value after calling the function, but
 * the output won't correspond to the correct encoded stream for the input
 * sequence.
 *
 * Return the size of the encoded output @out.
 */
size_t vtenc_encode8(VtencEncoder *enc, const uint8_t *in, size_t in_len, uint8_t *out, size_t out_cap);
size_t vtenc_encode16(VtencEncoder *enc, const uint16_t *in, size_t in_len, uint8_t *out, size_t out_cap);
size_t vtenc_encode32(VtencEncoder *enc, const uint32_t *in, size_t in_len, uint8_t *out, size_t out_cap);
size_t vtenc_encode64(VtencEncoder *enc, const uint64_t *in, size_t in_len, uint8_t *out, size_t out_cap);

/**
 * vtenc_max_encoded_size* functions.
 *
 * Functions to calculate the maximum encoded size in bytes when encoding a
 * sequence of size @in_len with its corresponding vtenc_encode* function.
 *
 * Return an approximation of the encoded length, which is guaranteed to
 * be at least as big as the actual size.
 */
size_t vtenc_max_encoded_size8(size_t in_len);
size_t vtenc_max_encoded_size16(size_t in_len);
size_t vtenc_max_encoded_size32(size_t in_len);
size_t vtenc_max_encoded_size64(size_t in_len);

/**
 * typedef VtencDecoder - VTEnc decoder.
 */
typedef struct {
  /**
   * Indicates whether repeated values are allowed or not.
   */
  int allow_repeated_values;

  /**
   * Indicates whether to skip full subtrees or not.
   * This parameter is only applicable to sets, i.e. sequences with no repeated
   * values. It's ignored if `allow_repeated_values` is set to 1.
   */
  int skip_full_subtrees;

  /**
   * Minimum cluster length to serialise.
   */
  size_t min_cluster_length;

  /**
   * 'Returning state' after calling a decode function. It'll hold the error
   * code value if the decode function fails, or a 'VtencErrorNoError' value if
   * the function runs successfully.
   */
  VtencErrorCode last_error_code;
} VtencDecoder;

/**
 * vtenc_decoder_init - initialises decoder @dec.
 */
void vtenc_decoder_init(VtencDecoder *dec);

/**
 * vtenc_decode* functions.
 *
 * Functions to decode the stream of bytes @in into the already-allocated
 * sequence @out, using the VTEnc algorithm with the provided decoding
 * parameters.
 *
 * @dec: decoder. Provides decoding parameters and holds the returning state.
 * @in: input stream of bytes to be decoded.
 * @in_len: size of @in.
 * @out: output sequence.
 * @out_len: size of @out.
 *
 * In case of failure, @dec->last_error_code contains the error code after
 * calling the function. If the function didn't fail, it holds a
 * 'VtencErrorNoError' value.
 */
void vtenc_decode8(VtencDecoder *dec, const uint8_t *in, size_t in_len, uint8_t *out, size_t out_len);
void vtenc_decode16(VtencDecoder *dec, const uint8_t *in, size_t in_len, uint16_t *out, size_t out_len);
void vtenc_decode32(VtencDecoder *dec, const uint8_t *in, size_t in_len, uint32_t *out, size_t out_len);
void vtenc_decode64(VtencDecoder *dec, const uint8_t *in, size_t in_len, uint64_t *out, size_t out_len);

#ifdef __cplusplus
}
#endif

#endif /* VTENC_H_ */
