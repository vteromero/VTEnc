/**
  Copyright (c) 2019 Vicente Romero Calero. All rights reserved.
  Licensed under the MIT License.
  See LICENSE file in the project root for full license information.
 */
#ifndef VTENC_INTERNALS_H_
#define VTENC_INTERNALS_H_

#include "bits.h"
#include "vtenc.h"

/* Shared macros */
#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define PASTE2(x, y) x ## y
#define PASTE3(x, y, z) x ## y ## z
#define BITWIDTH_SUFFIX(_name_, _width_) PASTE2(_name_, _width_)

/* Bitstream constants */
#define BIT_STREAM_MAX_WRITE  57
#define BIT_STREAM_MAX_READ   BIT_STREAM_MAX_WRITE

/* VTEnc constants */
#define VTENC_MAX_VALUES_LIMIT    BITS_SIZE_MASK[BIT_STREAM_MAX_WRITE]

#define VTENC_LIST_MAX_VALUES     VTENC_MAX_VALUES_LIMIT

#define VTENC_SET_MAX_VALUES8     MIN(BITS_POS_MASK64[8], VTENC_MAX_VALUES_LIMIT)
#define VTENC_SET_MAX_VALUES16    MIN(BITS_POS_MASK64[16], VTENC_MAX_VALUES_LIMIT)
#define VTENC_SET_MAX_VALUES32    MIN(BITS_POS_MASK64[32], VTENC_MAX_VALUES_LIMIT)
#define VTENC_SET_MAX_VALUES64    MIN(BITS_SIZE_MASK[64], VTENC_MAX_VALUES_LIMIT)

/* Encoding/decoding handler structure */
struct vtenc {
  struct vtenc_enc_params {     /* Encoding parameters */
    int allow_repeated_values;  /* 1 if repeated values are allowed */
    int skip_full_subtrees;     /* 1 to skip full subtrees */
    size_t min_cluster_length;  /* Minimum cluster length to serialise */
  } params;
  size_t out_size;              /* Output size in bytes */
};

/* Error-handling helper macro */
#define return_if_error(exp)  \
do {                          \
  const int code = (exp);     \
  if (code != VTENC_OK) {     \
    return code;              \
  }                           \
} while(0)

#endif /* VTENC_INTERNALS_H_ */
