/**
  Copyright (c) 2019 Vicente Romero Calero. All rights reserved.
  Licensed under the MIT License.
  See LICENSE file in the project root for full license information.
 */
#ifndef VTENC_BITSTREAM_H_
#define VTENC_BITSTREAM_H_

#include <assert.h>
#include <stddef.h>
#include <stdint.h>

#include "compiler.h"
#include "internals.h"
#include "mem.h"

struct bswriter {
  uint64_t      bit_container;
  unsigned int  bit_pos;
  uint8_t       *start_ptr;
  uint8_t       *ptr;
  uint8_t       *end_ptr;
};

static inline size_t bswriter_align_buffer_size(size_t orig_size)
{
  return orig_size + 8;
}

static inline int bswriter_init(struct bswriter *writer,
  uint8_t *out_buf, size_t out_capacity)
{
  if (out_capacity < sizeof(writer->bit_container)) {
    return VTENC_ERR_BUFFER_TOO_SMALL;
  }

  writer->bit_container = 0;
  writer->bit_pos = 0;
  writer->start_ptr = out_buf;
  writer->ptr = writer->start_ptr;
  writer->end_ptr = writer->start_ptr + out_capacity - sizeof(writer->bit_container);

  return VTENC_OK;
}

static inline void bswriter_append(struct bswriter *writer,
  uint64_t value, unsigned int n_bits)
{
  assert(n_bits <= BIT_STREAM_MAX_WRITE);
  assert(n_bits + writer->bit_pos < 64);

  writer->bit_container |= value << writer->bit_pos;
  writer->bit_pos += n_bits;
}

static inline void bswriter_flush(struct bswriter *writer)
{
  const unsigned int n_bytes = writer->bit_pos >> 3;

  assert(writer->ptr < writer->end_ptr);
  mem_write_le_u64(writer->ptr, writer->bit_container);

  writer->ptr += n_bytes;
  writer->bit_pos &= 7;
  writer->bit_container >>= (n_bytes << 3);
}

static inline void bswriter_write(struct bswriter *writer,
  uint64_t value, unsigned int n_bits)
{
  const unsigned int total_bits = writer->bit_pos + n_bits;
  const unsigned int n_bytes = total_bits >> 3;

  writer->bit_container |= value << writer->bit_pos;

  assert(writer->ptr < writer->end_ptr);
  mem_write_le_u64(writer->ptr, writer->bit_container);

  writer->ptr += n_bytes;
  writer->bit_pos = total_bits & 7;
  writer->bit_container >>= (n_bytes << 3);
}

static inline size_t bswriter_size(struct bswriter *writer)
{
  return (writer->ptr - writer->start_ptr) + (writer->bit_pos > 0);
}

struct bsreader {
  uint64_t      bit_container;
  unsigned int  bit_pos;
  const uint8_t *start_ptr;
  const uint8_t *ptr;
  const uint8_t *end_ptr;
};

static inline void bsreader_init(struct bsreader *reader,
  const uint8_t *buf, size_t buf_len)
{
  reader->bit_container = 0;
  reader->bit_pos = 0;
  reader->start_ptr = buf;
  reader->ptr = reader->start_ptr;
  reader->end_ptr = reader->start_ptr + buf_len;
}

static inline void bsreader_read(struct bsreader *reader,
  unsigned int n_bits, uint64_t *read_value)
{
  const unsigned int n_bytes = reader->end_ptr - reader->ptr;

  assert(reader->ptr < reader->end_ptr);

  if (n_bytes >= 8) {
    reader->bit_container = mem_read_le_u64(reader->ptr);
  } else {
    reader->bit_container = (uint64_t)(reader->ptr[0]);
    switch (n_bytes) {
      case 7: reader->bit_container |= (uint64_t)(reader->ptr[6]) << 48;
      case 6: reader->bit_container |= (uint64_t)(reader->ptr[5]) << 40;
      case 5: reader->bit_container |= (uint64_t)(reader->ptr[4]) << 32;
      case 4: reader->bit_container |= (uint64_t)(reader->ptr[3]) << 24;
      case 3: reader->bit_container |= (uint64_t)(reader->ptr[2]) << 16;
      case 2: reader->bit_container |= (uint64_t)(reader->ptr[1]) << 8;
      default: break;
    }
  }

  *read_value = (reader->bit_container >> reader->bit_pos) & ((1ULL << n_bits) - 1ULL);
  reader->ptr += (reader->bit_pos + n_bits) >> 3;
  reader->bit_pos = (reader->bit_pos + n_bits) & 7;
}

static inline size_t bsreader_size(struct bsreader *reader)
{
  return (reader->ptr - reader->start_ptr) + (reader->bit_pos >> 3) + ((reader->bit_pos & 7) > 0);
}

#endif /* VTENC_BITSTREAM_H_ */
