/**
  Copyright (c) 2019 Vicente Romero Calero. All rights reserved.
  Licensed under the MIT License.
  See LICENSE file in the project root for full license information.
 */
#ifndef VTENC_INTERNALS_H_
#define VTENC_INTERNALS_H_

#include "bits.h"
#include "bitstream.h"

/* Shared macros */

#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define PASTE2(x, y) x ## y
#define PASTE3(x, y, z) x ## y ## z
#define WIDTH_SUFFIX(_name_, _width_) PASTE2(_name_, _width_)

/* VTEnc constants */

#define VTENC_MAX_VALUES_LIMIT    BITS_SIZE_MASK[BIT_STREAM_MAX_WRITE]

#define VTENC_LIST_MAX_VALUES     VTENC_MAX_VALUES_LIMIT

#define VTENC_SET_MAX_VALUES8     MIN(BITS_POS_MASK64[8], VTENC_MAX_VALUES_LIMIT)
#define VTENC_SET_MAX_VALUES16    MIN(BITS_POS_MASK64[16], VTENC_MAX_VALUES_LIMIT)
#define VTENC_SET_MAX_VALUES32    MIN(BITS_POS_MASK64[32], VTENC_MAX_VALUES_LIMIT)
#define VTENC_SET_MAX_VALUES64    MIN(BITS_SIZE_MASK[64], VTENC_MAX_VALUES_LIMIT)

#endif /* VTENC_INTERNALS_H_ */
