/**
  Copyright (c) 2021 Vicente Romero Calero. All rights reserved.
  Licensed under the MIT License.
  See LICENSE file in the project root for full license information.
 */
#ifndef VTENC_STACK_H_
#define VTENC_STACK_H_

#include <stddef.h>
#include <string.h>

#define DEFINE_STACK_STRUCT(name, type, max_size) \
  struct name {                                   \
    type    data[max_size];                       \
    size_t  head;                                 \
  }

#define DEFINE_STACK_INIT_FN(name)                \
  static inline void name##_init(struct name *s)  \
  {                                               \
    s->head = 0;                                  \
  }

#define DEFINE_STACK_EMPTY_FN(name)                 \
  static inline int name##_empty(struct name *s)    \
  {                                                 \
    return s->head == 0;                            \
  }

#define DEFINE_STACK_SIZE_FN(name)                  \
  static inline size_t name##_size(struct name *s)  \
  {                                                 \
    return s->head;                                 \
  }

#define DEFINE_STACK_PUSH_FN(name, type)                              \
  static inline void name##_push(struct name *s, const type *element) \
  {                                                                   \
    memcpy(s->data + s->head, element, sizeof(type));                 \
    s->head++;                                                        \
  }

#define DEFINE_STACK_POP_FN(name, type)           \
  static inline type *name##_pop(struct name *s)  \
  {                                               \
    return &s->data[--s->head];                   \
  }

/**
 * Creates a LIFO stack with a fixed maximum size `max_size`.
 */
#define CREATE_STACK(name, type, max_size)    \
  DEFINE_STACK_STRUCT(name, type, max_size);  \
  DEFINE_STACK_INIT_FN(name)                  \
  DEFINE_STACK_EMPTY_FN(name)                 \
  DEFINE_STACK_SIZE_FN(name)                  \
  DEFINE_STACK_PUSH_FN(name, type)            \
  DEFINE_STACK_POP_FN(name, type)

#endif /* VTENC_STACK_H_ */
