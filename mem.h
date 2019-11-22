/**
  Copyright (c) 2019 Vicente Romero Calero. All rights reserved.
  Licensed under the MIT License.
  See LICENSE file in the project root for full license information.
 */
#ifndef VTENC_MEM_H_
#define VTENC_MEM_H_

#include <stdint.h>
#include <string.h>

#include "bits.h"

static inline unsigned mem_is_little_endian(void)
{
  const union { uint32_t u; uint8_t c[4]; } one = { 1 };
  return one.c[0];
}

/* Generic read functions */

static inline uint16_t mem_read_u16(const void* mem_ptr)
{
  uint16_t value;
  memcpy(&value, mem_ptr, sizeof(value));
  return value;
}

static inline uint32_t mem_read_u32(const void* mem_ptr)
{
  uint32_t value;
  memcpy(&value, mem_ptr, sizeof(value));
  return value;
}

static inline uint64_t mem_read_u64(const void* mem_ptr)
{
  uint64_t value;
  memcpy(&value, mem_ptr, sizeof(value));
  return value;
}

/* Generic write functions */

static inline void mem_write_u16(void* mem_ptr, uint16_t value)
{
  memcpy(mem_ptr, &value, sizeof(value));
}

static inline void mem_write_u32(void* mem_ptr, uint32_t value)
{
  memcpy(mem_ptr, &value, sizeof(value));
}

static inline void mem_write_u64(void* mem_ptr, uint64_t value)
{
  memcpy(mem_ptr, &value, sizeof(value));
}

/* Little endian read functions */

static inline uint16_t mem_read_le_u16(const void* mem_ptr)
{
  if (mem_is_little_endian())
    return mem_read_u16(mem_ptr);
  else
    return bits_swap_u16(mem_read_u16(mem_ptr));
}

static inline uint32_t mem_read_le_u32(const void* mem_ptr)
{
  if (mem_is_little_endian())
    return mem_read_u32(mem_ptr);
  else
    return bits_swap_u32(mem_read_u32(mem_ptr));
}

static inline uint64_t mem_read_le_u64(const void* mem_ptr)
{
  if (mem_is_little_endian())
    return mem_read_u64(mem_ptr);
  else
    return bits_swap_u64(mem_read_u64(mem_ptr));
}

/* Little endian write functions */

static inline void mem_write_le_u16(void* mem_ptr, uint16_t value)
{
  if (mem_is_little_endian())
    mem_write_u16(mem_ptr, value);
  else
    mem_write_u16(mem_ptr, bits_swap_u16(value));
}

static inline void mem_write_le_u32(void* mem_ptr, uint32_t value)
{
  if (mem_is_little_endian())
    mem_write_u32(mem_ptr, value);
  else
    mem_write_u32(mem_ptr, bits_swap_u32(value));
}

static inline void mem_write_le_u64(void* mem_ptr, uint64_t value)
{
  if (mem_is_little_endian())
    mem_write_u64(mem_ptr, value);
  else
    mem_write_u64(mem_ptr, bits_swap_u64(value));
}

#endif /* VTENC_MEM_H_ */
