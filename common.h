#ifndef VTENC_COMMON_H_
#define VTENC_COMMON_H_

#include <stddef.h>
#include <stdint.h>

#include "bits.h"

static unsigned int is_full_subtree(size_t values_len, unsigned int bit_pos)
{
  return ((uint64_t)values_len == BITS_POS_MASK[bit_pos + 1]);
}

#endif /* VTENC_COMMON_H_ */
