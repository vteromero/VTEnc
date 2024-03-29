/**
  Copyright (c) 2022 Vicente Romero Calero. All rights reserved.
  Licensed under the MIT License.
  See LICENSE file in the project root for full license information.
 */
#include "bitstream.h"
#include "internals.h"

#define batch_(_width_, _n_) PASTE4(batch, _width_, _, _n_)
#define batch1               batch_(BITWIDTH, 1)
#define batch2               batch_(BITWIDTH, 2)
#define batch3               batch_(BITWIDTH, 3)
#define batch4               batch_(BITWIDTH, 4)

static inline void batch1(
  struct bswriter *writer,
  const TYPE *values,
  unsigned int n_bits)
{
#if BITWIDTH == 64
  uint64_t value = values[0];
  if (n_bits > BIT_STREAM_MAX_WRITE) {
    bswriter_append(writer, value, BIT_STREAM_MAX_WRITE);
    bswriter_flush(writer);
    value >>= BIT_STREAM_MAX_WRITE;
    n_bits -= BIT_STREAM_MAX_WRITE;
  }
  bswriter_append(writer, value, n_bits);
  bswriter_flush(writer);
#else
  bswriter_append(writer, values[0], n_bits);
  bswriter_flush(writer);
#endif
}

static inline void batch2(
  struct bswriter *writer,
  const TYPE *values,
  unsigned int n_bits)
{
  bswriter_append(writer, values[0], n_bits);
  bswriter_append(writer, values[1], n_bits);
  bswriter_flush(writer);
}

static inline void batch3(
  struct bswriter *writer,
  const TYPE *values,
  unsigned int n_bits)
{
  bswriter_append(writer, values[0], n_bits);
  bswriter_append(writer, values[1], n_bits);
  bswriter_append(writer, values[2], n_bits);
  bswriter_flush(writer);
}

static inline void batch4(
  struct bswriter *writer,
  const TYPE *values,
  unsigned int n_bits)
{
  bswriter_append(writer, values[0], n_bits);
  bswriter_append(writer, values[1], n_bits);
  bswriter_append(writer, values[2], n_bits);
  bswriter_append(writer, values[3], n_bits);
  bswriter_flush(writer);
}

#define in_batches_(_width_, _n_) PASTE4(in_batches, _width_, _, _n_)
#define in_batches1               in_batches_(BITWIDTH, 1)
#define in_batches2               in_batches_(BITWIDTH, 2)
#define in_batches3               in_batches_(BITWIDTH, 3)
#define in_batches4               in_batches_(BITWIDTH, 4)

static inline void in_batches1(
  struct bswriter *writer,
  const TYPE *values,
  size_t values_len,
  unsigned int n_bits)
{
  size_t i;

  for (i = 0; i < values_len; i++) {
    batch1(writer, values + i, n_bits);
  }
}

static inline void in_batches2(
  struct bswriter *writer,
  const TYPE *values,
  size_t values_len,
  unsigned int n_bits)
{
  while (values_len >= 2) {
    batch2(writer, values, n_bits);
    values += 2;
    values_len -= 2;
  }

  in_batches1(writer, values, values_len, n_bits);
}

static inline void in_batches3(
  struct bswriter *writer,
  const TYPE *values,
  size_t values_len,
  unsigned int n_bits)
{
  while (values_len >= 3) {
    batch3(writer, values, n_bits);
    values += 3;
    values_len -= 3;
  }

  in_batches1(writer, values, values_len, n_bits);
}

static inline void in_batches4(
  struct bswriter *writer,
  const TYPE *values,
  size_t values_len,
  unsigned int n_bits)
{
  while (values_len >= 4) {
    batch4(writer, values, n_bits);
    values += 4;
    values_len -= 4;
  }

  in_batches1(writer, values, values_len, n_bits);
}

#define encode_lower_bits_(_width_) BITWIDTH_SUFFIX(encode_lower_bits, _width_)
#define encode_lower_bits           encode_lower_bits_(BITWIDTH)

static inline void encode_lower_bits(
  struct bswriter *writer,
  const TYPE *values,
  size_t values_len,
  unsigned int n_bits)
{
  switch (batch_sz_table[n_bits]) {
    case 1: in_batches1(writer, values, values_len, n_bits); break;
    case 2: in_batches2(writer, values, values_len, n_bits); break;
    case 3: in_batches3(writer, values, values_len, n_bits); break;
    case 4: in_batches4(writer, values, values_len, n_bits); break;
  }
}
