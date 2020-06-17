/**
  Copyright (c) 2019-2020 Vicente Romero Calero. All rights reserved.
  Licensed under the MIT License.
  See LICENSE file in the project root for full license information.
 */
#ifndef VTENC_BITCLUSTER_H_
#define VTENC_BITCLUSTER_H_

#include <assert.h>
#include <stddef.h>
#include <stdlib.h>

struct BitCluster {
  size_t from;
  size_t length;
  unsigned int bit_pos;
};

#define BIT_CLUSTER_STACK_MAX_SIZE 64

/**
 * BitClusterStack is a LIFO stack with a fixed maximum size.
 */
struct BitClusterStack {
  struct BitCluster clusters[BIT_CLUSTER_STACK_MAX_SIZE];
  size_t head;
};

static inline void bclstack_init(struct BitClusterStack *s)
{
  s->head = 0;
}

static inline int bclstack_empty(struct BitClusterStack *s)
{
  return s->head == 0;
}

static inline size_t bclstack_length(struct BitClusterStack *s)
{
  return s->head;
}

static inline void bclstack_put(struct BitClusterStack *s,
  size_t from, size_t length, unsigned int bit_pos)
{
  assert(s->head < BIT_CLUSTER_STACK_MAX_SIZE);

  s->clusters[s->head++] = (struct BitCluster) {
    .from = from,
    .length = length,
    .bit_pos = bit_pos
  };
}

static inline struct BitCluster *bclstack_get(struct BitClusterStack *s)
{
  if (bclstack_empty(s)) return NULL;

  return &s->clusters[--s->head];
}

#endif /* VTENC_BITCLUSTER_H_ */
