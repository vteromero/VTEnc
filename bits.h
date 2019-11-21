/**
  Copyright (c) 2019 Vicente Romero Calero. All rights reserved.
  Licensed under the MIT License.
  See LICENSE file in the project root for full license information.
 */
#ifndef VTENC_BITS_H_
#define VTENC_BITS_H_

#include <stdint.h>

static const uint64_t BITS_SIZE_MASK[] = {
                 0x0ULL,
	               0x1ULL,                0x3ULL,                0x7ULL,                0xfULL,
	              0x1fULL,               0x3fULL,               0x7fULL,               0xffULL,
	             0x1ffULL,              0x3ffULL,              0x7ffULL,              0xfffULL,
	            0x1fffULL,             0x3fffULL,             0x7fffULL,             0xffffULL,
	           0x1ffffULL,            0x3ffffULL,            0x7ffffULL,            0xfffffULL,
	          0x1fffffULL,           0x3fffffULL,           0x7fffffULL,           0xffffffULL,
	         0x1ffffffULL,          0x3ffffffULL,          0x7ffffffULL,          0xfffffffULL,
	        0x1fffffffULL,         0x3fffffffULL,         0x7fffffffULL,         0xffffffffULL,
	       0x1ffffffffULL,        0x3ffffffffULL,        0x7ffffffffULL,        0xfffffffffULL,
	      0x1fffffffffULL,       0x3fffffffffULL,       0x7fffffffffULL,       0xffffffffffULL,
	     0x1ffffffffffULL,      0x3ffffffffffULL,      0x7ffffffffffULL,      0xfffffffffffULL,
	    0x1fffffffffffULL,     0x3fffffffffffULL,     0x7fffffffffffULL,     0xffffffffffffULL,
	   0x1ffffffffffffULL,    0x3ffffffffffffULL,    0x7ffffffffffffULL,    0xfffffffffffffULL,
	  0x1fffffffffffffULL,   0x3fffffffffffffULL,   0x7fffffffffffffULL,   0xffffffffffffffULL,
	 0x1ffffffffffffffULL,  0x3ffffffffffffffULL,  0x7ffffffffffffffULL,  0xfffffffffffffffULL,
  0x1fffffffffffffffULL, 0x3fffffffffffffffULL, 0x7fffffffffffffffULL, 0xffffffffffffffffULL
};
#define BITS_SIZE_MASK_LEN (sizeof(BITS_SIZE_MASK) / sizeof(BITS_SIZE_MASK[0]))

static const uint64_t BITS_POS_MASK[] = {
                 0x1ULL,                0x2ULL,                0x4ULL,                0x8ULL,
                0x10ULL,               0x20ULL,               0x40ULL,               0x80ULL,
               0x100ULL,              0x200ULL,              0x400ULL,              0x800ULL,
              0x1000ULL,             0x2000ULL,             0x4000ULL,             0x8000ULL,
             0x10000ULL,            0x20000ULL,            0x40000ULL,            0x80000ULL,
            0x100000ULL,           0x200000ULL,           0x400000ULL,           0x800000ULL,
           0x1000000ULL,          0x2000000ULL,          0x4000000ULL,          0x8000000ULL,
          0x10000000ULL,         0x20000000ULL,         0x40000000ULL,         0x80000000ULL,
         0x100000000ULL,        0x200000000ULL,        0x400000000ULL,        0x800000000ULL,
        0x1000000000ULL,       0x2000000000ULL,       0x4000000000ULL,       0x8000000000ULL,
       0x10000000000ULL,      0x20000000000ULL,      0x40000000000ULL,      0x80000000000ULL,
      0x100000000000ULL,     0x200000000000ULL,     0x400000000000ULL,     0x800000000000ULL,
     0x1000000000000ULL,    0x2000000000000ULL,    0x4000000000000ULL,    0x8000000000000ULL,
    0x10000000000000ULL,   0x20000000000000ULL,   0x40000000000000ULL,   0x80000000000000ULL,
   0x100000000000000ULL,  0x200000000000000ULL,  0x400000000000000ULL,  0x800000000000000ULL,
  0x1000000000000000ULL, 0x2000000000000000ULL, 0x4000000000000000ULL, 0x8000000000000000ULL
};
#define BITS_POS_MASK_LEN (sizeof(BITS_POS_MASK) / sizeof(BITS_POS_MASK[0]))

static const unsigned int BITS_LEN8[] = {
  1, 1, 2, 2, 3, 3, 3, 3, 4, 4, 4, 4, 4, 4, 4, 4,
  5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5,
  6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6,
  6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6,
  7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
  7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
  7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
  7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
  8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8,
  8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8,
  8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8,
  8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8,
  8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8,
  8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8,
  8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8,
  8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8
};

static inline uint16_t bits_swap_u16(uint16_t value)
{
  return (value << 8) | (value >> 8);
}

static inline uint32_t bits_swap_u32(uint32_t value)
{
  return  ((value << 24) & 0xff000000 ) |
          ((value <<  8) & 0x00ff0000 ) |
          ((value >>  8) & 0x0000ff00 ) |
          ((value >> 24) & 0x000000ff );
}

static inline uint64_t bits_swap_u64(uint64_t value)
{
  return  ((value << 56) & 0xff00000000000000ULL) |
          ((value << 40) & 0x00ff000000000000ULL) |
          ((value << 24) & 0x0000ff0000000000ULL) |
          ((value << 8)  & 0x000000ff00000000ULL) |
          ((value >> 8)  & 0x00000000ff000000ULL) |
          ((value >> 24) & 0x0000000000ff0000ULL) |
          ((value >> 40) & 0x000000000000ff00ULL) |
          ((value >> 56) & 0x00000000000000ffULL);
}

static inline unsigned int bits_len_u8(uint8_t value)
{
  return BITS_LEN8[value];
}

static inline unsigned int bits_len_u16(uint16_t value)
{
  unsigned int n = 0;

  if (value > 0x00ff) {
    value >>= 8;
    n = 8;
  }

  return n + BITS_LEN8[value];
}

static inline unsigned int bits_len_u32(uint32_t value)
{
  unsigned int n = 0;

  if (value > 0x0000ffff) {
    value >>= 16;
    n = 16;
  }
  if (value > 0x000000ff) {
    value >>= 8;
    n += 8;
  }

  return n + BITS_LEN8[value];
}

static inline unsigned int bits_len_u64(uint64_t value)
{
  unsigned int n = 0;

  if (value > 0x00000000ffffffffULL) {
    value >>= 32;
    n = 32;
  }
  if (value > 0x000000000000ffffULL) {
    value >>= 16;
    n += 16;
  }
  if (value > 0x00000000000000ffULL) {
    value >>= 8;
    n += 8;
  }

  return n + BITS_LEN8[value];
}

#endif /* VTENC_BITS_H_ */
