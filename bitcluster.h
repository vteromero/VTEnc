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
#include <string.h>

struct BitCluster {
  size_t from;
  size_t length;
  unsigned int bit_pos;
};

/**
 * BitClusterQueue is a FIFO queue with a fixed maximum size. It is implemented
 * as a circular queue so that no extra re-allocations are required.
 */
struct BitClusterQueue {
  struct BitCluster *start;
  struct BitCluster *end;
  struct BitCluster *back;
  struct BitCluster *front;
};

static struct BitClusterQueue *bclqueue_new(size_t max_size)
{
  struct BitClusterQueue *q = NULL;
  size_t alloc_size = max_size + 1;

  assert(max_size > 0);

  q = (struct BitClusterQueue *) malloc(sizeof(struct BitClusterQueue));
  if (q == NULL) return NULL;

  q->start = (struct BitCluster *) malloc(alloc_size * sizeof(struct BitCluster));
  if (q->start == NULL) {
    free(q);
    return NULL;
  }

  q->end = q->start + alloc_size;
  q->back = q->start;
  q->front = q->start;

  return q;
}

static inline void bclqueue_free(struct BitClusterQueue **q)
{
  free((*q)->start);
  free(*q);
}

static inline size_t bclqueue_length(struct BitClusterQueue *q)
{
  if (q->front < q->back) {
    return (q->end - q->back) + (q->front - q->start);
  } else {
    return q->front - q->back;
  }
}

static inline int bclqueue_empty(struct BitClusterQueue *q)
{
  return q->front == q->back;
}

static inline void bclqueue_put(struct BitClusterQueue *q, size_t cl_from,
  size_t cl_len, unsigned int bit_pos)
{
  *(q->front) = (struct BitCluster) {
    .from = cl_from,
    .length = cl_len,
    .bit_pos = bit_pos
  };

  q->front = (++q->front == q->end) ? q->start : q->front;

  assert(q->front != q->back);
}

static inline struct BitCluster *bclqueue_get(struct BitClusterQueue *q)
{
  struct BitCluster *cluster = NULL;

  if (bclqueue_empty(q)) return NULL;

  cluster = q->back;
  q->back = (++q->back == q->end) ? q->start : q->back;

  return cluster;
}

#endif /* VTENC_BITCLUSTER_H_ */
