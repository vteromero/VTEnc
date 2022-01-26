/**
  Copyright (c) 2019 Vicente Romero Calero. All rights reserved.
  Licensed under the MIT License.
  See LICENSE file in the project root for full license information.
 */
#include "vtenc.h"

#include "internals.h"
#include "stack.h"

void vtenc_encoder_init(VtencEncoder *enc)
{
  enc->allow_repeated_values  = 1;
  enc->skip_full_subtrees     = 1;
  enc->min_cluster_length     = 1;
  enc->last_error_code        = VtencErrorNoError;
}

#define ENCODE_STACK_MAX_SIZE 64

struct encode_bit_cluster {
  size_t from;
  size_t length;
  unsigned int bit_pos;
};

CREATE_STACK(encode_stack, struct encode_bit_cluster, ENCODE_STACK_MAX_SIZE)

#define LIST_MAX_VALUES VTENC_LIST_MAX_VALUES

#define TYPE uint8_t
#define WIDTH 8
#define SET_MAX_VALUES VTENC_SET_MAX_VALUES8
#include "encode_generic.h"
#undef TYPE
#undef WIDTH
#undef SET_MAX_VALUES

#define TYPE uint16_t
#define WIDTH 16
#define SET_MAX_VALUES VTENC_SET_MAX_VALUES16
#include "encode_generic.h"
#undef TYPE
#undef WIDTH
#undef SET_MAX_VALUES

#define TYPE uint32_t
#define WIDTH 32
#define SET_MAX_VALUES VTENC_SET_MAX_VALUES32
#include "encode_generic.h"
#undef TYPE
#undef WIDTH
#undef SET_MAX_VALUES

#define TYPE uint64_t
#define WIDTH 64
#define SET_MAX_VALUES VTENC_SET_MAX_VALUES64
#include "encode_generic.h"
#undef TYPE
#undef WIDTH
#undef SET_MAX_VALUES

#undef LIST_MAX_VALUES
