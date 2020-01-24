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

struct BitClusterQueue {
  struct BitCluster *start;
  struct BitCluster *end;
  struct BitCluster *back;
  struct BitCluster *front;
};

static inline struct BitClusterQueue *bclqueue_new(size_t cap)
{
  struct BitClusterQueue *q = NULL;

  assert(cap > 0);

  q = (struct BitClusterQueue *) malloc(sizeof(struct BitClusterQueue));
  if (q == NULL) return NULL;

  q->start = (struct BitCluster *) malloc(cap * sizeof(struct BitCluster));
  if (q->start == NULL) {
    free(q);
    return NULL;
  }

  q->end = q->start + cap;
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
  assert(q->front >= q->back);

  return q->front - q->back;
}

static inline int bclqueue_empty(struct BitClusterQueue *q)
{
  return bclqueue_length(q) == 0;
}

static inline void bclqueue_restructure(struct BitClusterQueue *q)
{
  size_t q_len = bclqueue_length(q);

  if (q->back == q->start) return;

  if (!bclqueue_empty(q))
    memcpy(q->start, q->back, q_len * sizeof(struct BitCluster));

  q->back = q->start;
  q->front = q->back + q_len;
}

static inline void bclqueue_put(struct BitClusterQueue *q, size_t cl_from,
  size_t cl_len, unsigned int bit_pos)
{
  if (q->front == q->end) bclqueue_restructure(q);

  assert(q->front < q->end);

  *(q->front) = (struct BitCluster) {
    .from = cl_from,
    .length = cl_len,
    .bit_pos = bit_pos
  };
  q->front++;
}

static inline struct BitCluster *bclqueue_get(struct BitClusterQueue *q)
{
  if (bclqueue_empty(q)) return NULL;

  return q->back++;
}

#endif /* VTENC_BITCLUSTER_H_ */
