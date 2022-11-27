/**
  Copyright (c) 2022 Vicente Romero Calero. All rights reserved.
  Licensed under the MIT License.
  See LICENSE file in the project root for full license information.
 */
#ifndef VTENC_ENCODEBITS_H_
#define VTENC_ENCODEBITS_H_

#include <stddef.h>
#include <stdint.h>

static const size_t batch_sz_table[65] = {
  4, 4, 4, 4, 4, 4, 4, 4,
  4, 4, 4, 4, 4, 4, 4, 3,
  3, 3, 3, 2, 2, 2, 2, 2,
  2, 2, 2, 2, 2, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1,
  1
};

#define TYPE uint8_t
#define BITWIDTH 8
#include "encodebits.inc.h"
#undef TYPE
#undef BITWIDTH

#define TYPE uint16_t
#define BITWIDTH 16
#include "encodebits.inc.h"
#undef TYPE
#undef BITWIDTH

#define TYPE uint32_t
#define BITWIDTH 32
#include "encodebits.inc.h"
#undef TYPE
#undef BITWIDTH

#define TYPE uint64_t
#define BITWIDTH 64
#include "encodebits.inc.h"
#undef TYPE
#undef BITWIDTH

#endif /* VTENC_ENCODEBITS_H_ */
