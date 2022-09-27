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
#define VTENC_ERR_INPUT_TOO_BIG     (-3)  /* Input size too big */
#define VTENC_ERR_OUTPUT_TOO_BIG    (-4)  /* Output size too big */
#define VTENC_ERR_WRONG_FORMAT      (-5)  /* Wrong encoded format */
#define VTENC_ERR_CONFIG            (-6)  /* Unrecognised config option */

/* Encoding/decoding handler */
typedef struct vtenc vtenc;

/* Create a new encoding/decoding handler */
vtenc *vtenc_create(void);

/* Destroy an encoding/decoding handler */
void vtenc_destroy(vtenc *handler);

/*
 * Configuration options.
 *
 * These constants are the available integer options that can be passed as the
 * second argument to the vtenc_config() function.
 *
 * VTENC_CONFIG_ALLOW_REPEATED_VALUES takes a single argument of type int. If
 * non-zero, the sequence to be encoded or decoded can have repeated values.
 * If the parameter is zero, the sequence is considered to be a set with no
 * repeated values.
 *
 * VTENC_CONFIG_SKIP_FULL_SUBTREES takes a single argument of type int. If
 * non-zero, full subtrees are skipped to be encoded, meaning that children
 * nodes in a full subtree are not part of the encoded stream. If argument is
 * zero, this functionality is disabled.
 * VTENC_CONFIG_SKIP_FULL_SUBTREES is only relevant to sets, so this config
 * will be ignored when VTENC_CONFIG_ALLOW_REPEATED_VALUES is set to a non-zero
 * value.
 *
 * VTENC_CONFIG_MIN_CLUSTER_LENGTH takes a single argument of type size_t. It
 * sets the minimun cluster length that is encoded.
 */
#define VTENC_CONFIG_ALLOW_REPEATED_VALUES  0   /* int */
#define VTENC_CONFIG_SKIP_FULL_SUBTREES     1   /* int */
#define VTENC_CONFIG_MIN_CLUSTER_LENGTH     2   /* size_t */
#define VTENC_CONFIG_BIT_WIDTH              3   /* unsigned int */

/* Configure encoding/decoding handler */
int vtenc_config(vtenc *handler, int op, ...);

/**
 * vtenc_encode* functions.
 *
 * Functions to encode the sequence @in into the already-allocated stream of
 * bytes @out, using the VTEnc algorithm with the provided encoding parameters.
 *
 * @enc: encoder. Provides encoding parameters.
 * @in: input sequence to be encoded.
 * @in_len: size of @in.
 * @out: output stream of bytes.
 * @out_cap: capacity of @out / number of allocated bytes in @out.
 *
 * Returns VTENC_OK if the encoding is successful. Otherwise, an error code
 * will be returned (see result codes for more info).
 *
 * The output size can be obtained by calling vtenc_encoded_size() separately.
 *
 * Note that these functions assume that @in is a sorted sequence and they don't
 * check its order. If you pass in an unsorted sequence, you may still get a
 * VTENC_OK code, but the output won't necessarily correspond to the correct
 * encoded stream for the input sequence.
 */
int vtenc_encode8(vtenc *enc, const uint8_t *in, size_t in_len, uint8_t *out, size_t out_cap);
int vtenc_encode16(vtenc *enc, const uint16_t *in, size_t in_len, uint8_t *out, size_t out_cap);
int vtenc_encode32(vtenc *enc, const uint32_t *in, size_t in_len, uint8_t *out, size_t out_cap);
int vtenc_encode64(vtenc *enc, const uint64_t *in, size_t in_len, uint8_t *out, size_t out_cap);

/*
 * Returns the number of bytes of the output of calling a vtenc_encode* function.
 */
size_t vtenc_encoded_size(vtenc *enc);
size_t vtenc_encoded_size_bits(vtenc *enc);

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
 * vtenc_decode* functions.
 *
 * Functions to decode the stream of bytes @in into the already-allocated
 * sequence @out, using the VTEnc algorithm with the provided encoding
 * parameters.
 *
 * @dec: decoder. Provides encoding parameters.
 * @in: input stream of bytes to be decoded.
 * @in_len: size of @in.
 * @out: output sequence.
 * @out_len: size of @out.
 *
 * Returns VTENC_OK when the decoding is successful or an error code otherwise.
 *
 * Note that the size of the output (@out_len) needs to be known to call a
 * vtenc_decode* function.
 */
int vtenc_decode8(vtenc *dec, const uint8_t *in, size_t in_len, uint8_t *out, size_t out_len);
int vtenc_decode16(vtenc *dec, const uint8_t *in, size_t in_len, uint16_t *out, size_t out_len);
int vtenc_decode32(vtenc *dec, const uint8_t *in, size_t in_len, uint32_t *out, size_t out_len);
int vtenc_decode64(vtenc *dec, const uint8_t *in, size_t in_len, uint64_t *out, size_t out_len);

#ifdef __cplusplus
}
#endif

#endif /* VTENC_H_ */
