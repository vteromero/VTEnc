/**
  Copyright (c) 2019 Vicente Romero Calero. All rights reserved.
  Licensed under the MIT License.
  See LICENSE file in the project root for full license information.
 */
#include "vtenc.h"

#include "internals.h"
#include "stack.h"

void vtenc_decoder_init(VtencDecoder *dec)
{
  dec->allow_repeated_values  = 1;
  dec->skip_full_subtrees     = 1;
  dec->min_cluster_length     = 1;
  dec->last_error_code        = VtencErrorNoError;
}

#define DECODE_STACK_MAX_SIZE 64

struct dec_bit_cluster {
  size_t        from;
  size_t        length;
  unsigned int  bit_pos;
  uint64_t      higher_bits;
};

CREATE_STACK(dec_stack, struct dec_bit_cluster, DECODE_STACK_MAX_SIZE)

#define LIST_MAX_VALUES VTENC_LIST_MAX_VALUES

#define TYPE uint8_t
#define WIDTH 8
#define SET_MAX_VALUES VTENC_SET_MAX_VALUES8
#include "decode_generic.h"
#undef TYPE
#undef WIDTH
#undef SET_MAX_VALUES

#define TYPE uint16_t
#define WIDTH 16
#define SET_MAX_VALUES VTENC_SET_MAX_VALUES16
#include "decode_generic.h"
#undef TYPE
#undef WIDTH
#undef SET_MAX_VALUES

#define TYPE uint32_t
#define WIDTH 32
#define SET_MAX_VALUES VTENC_SET_MAX_VALUES32
#include "decode_generic.h"
#undef TYPE
#undef WIDTH
#undef SET_MAX_VALUES

#define TYPE uint64_t
#define WIDTH 64
#define SET_MAX_VALUES VTENC_SET_MAX_VALUES64
#include "decode_generic.h"
#undef TYPE
#undef WIDTH
#undef SET_MAX_VALUES

#undef LIST_MAX_VALUES
