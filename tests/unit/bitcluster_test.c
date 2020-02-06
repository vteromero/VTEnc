/**
  Copyright (c) 2019-2020 Vicente Romero Calero. All rights reserved.
  Licensed under the MIT License.
  See LICENSE file in the project root for full license information.
 */
#include "unit_tests.h"
#include "../../bitcluster.h"

int test_bclqueue_new(void)
{
  struct BitClusterQueue *q = bclqueue_new(10);

  EXPECT_TRUE(bclqueue_empty(q));

  bclqueue_free(&q);

  return 1;
}

int test_bclqueue_put_and_get_1(void)
{
  struct BitClusterQueue *q = bclqueue_new(10);
  struct BitCluster *cl;

  EXPECT_TRUE(bclqueue_get(q) == NULL);

  bclqueue_put(q, 0, 5, 0);
  bclqueue_put(q, 5, 2, 0);
  bclqueue_put(q, 7, 3, 1);

  EXPECT_TRUE(bclqueue_length(q) == 3);

  cl = bclqueue_get(q); EXPECT_TRUE(cl->from == 0); EXPECT_TRUE(cl->length == 5); EXPECT_TRUE(cl->bit_pos == 0);
  EXPECT_TRUE(bclqueue_length(q) == 2);

  cl = bclqueue_get(q); EXPECT_TRUE(cl->from == 5); EXPECT_TRUE(cl->length == 2); EXPECT_TRUE(cl->bit_pos == 0);
  EXPECT_TRUE(bclqueue_length(q) == 1);

  cl = bclqueue_get(q); EXPECT_TRUE(cl->from == 7); EXPECT_TRUE(cl->length == 3); EXPECT_TRUE(cl->bit_pos == 1);
  EXPECT_TRUE(bclqueue_length(q) == 0);
  EXPECT_TRUE(bclqueue_empty(q));

  EXPECT_TRUE(bclqueue_get(q) == NULL);

  bclqueue_free(&q);

  return 1;
}

int test_bclqueue_put_and_get_2(void)
{
  struct BitClusterQueue *q = bclqueue_new(3);
  struct BitCluster *cl;

  bclqueue_put(q, 0, 5, 0);
  bclqueue_put(q, 5, 2, 0);
  bclqueue_put(q, 7, 3, 1);
  EXPECT_TRUE(bclqueue_length(q) == 3);
  EXPECT_TRUE(!bclqueue_empty(q));

  EXPECT_TRUE(bclqueue_get(q) != NULL); EXPECT_TRUE(bclqueue_length(q) == 2);
  EXPECT_TRUE(bclqueue_get(q) != NULL); EXPECT_TRUE(bclqueue_length(q) == 1);
  EXPECT_TRUE(bclqueue_get(q) != NULL); EXPECT_TRUE(bclqueue_length(q) == 0);
  EXPECT_TRUE(bclqueue_empty(q));

  bclqueue_put(q, 100, 100, 15); EXPECT_TRUE(bclqueue_length(q) == 1);
  bclqueue_put(q, 200, 100, 16); EXPECT_TRUE(bclqueue_length(q) == 2);
  bclqueue_put(q, 300, 100, 17); EXPECT_TRUE(bclqueue_length(q) == 3);
  EXPECT_TRUE(!bclqueue_empty(q));

  cl = bclqueue_get(q); EXPECT_TRUE(cl->from == 100); EXPECT_TRUE(cl->length == 100); EXPECT_TRUE(cl->bit_pos == 15);
  cl = bclqueue_get(q); EXPECT_TRUE(cl->from == 200); EXPECT_TRUE(cl->length == 100); EXPECT_TRUE(cl->bit_pos == 16);
  cl = bclqueue_get(q); EXPECT_TRUE(cl->from == 300); EXPECT_TRUE(cl->length == 100); EXPECT_TRUE(cl->bit_pos == 17);

  EXPECT_TRUE(bclqueue_empty(q));

  bclqueue_free(&q);

  return 1;
}

int test_bclstack_new(void)
{
  struct BitClusterStack *s = bclstack_new(10);

  EXPECT_TRUE(bclstack_empty(s));

  bclstack_free(&s);

  return 1;
}

int test_bclstack_put_and_get(void)
{
  struct BitClusterStack *s = bclstack_new(3);
  struct BitCluster *cl;

  EXPECT_TRUE(bclstack_get(s) == NULL);

  bclstack_put(s, 0, 5, 0);
  bclstack_put(s, 5, 2, 0);
  bclstack_put(s, 7, 3, 1);

  EXPECT_TRUE(bclstack_length(s) == 3);

  cl = bclstack_get(s); EXPECT_TRUE(cl->from == 7); EXPECT_TRUE(cl->length == 3); EXPECT_TRUE(cl->bit_pos == 1);
  cl = bclstack_get(s); EXPECT_TRUE(cl->from == 5); EXPECT_TRUE(cl->length == 2); EXPECT_TRUE(cl->bit_pos == 0);

  EXPECT_TRUE(bclstack_length(s) == 1);

  bclstack_put(s, 999, 888, 777);
  bclstack_put(s, 12, 34, 56);

  EXPECT_TRUE(bclstack_length(s) == 3);

  cl = bclstack_get(s); EXPECT_TRUE(cl->from == 12); EXPECT_TRUE(cl->length == 34); EXPECT_TRUE(cl->bit_pos == 56);
  cl = bclstack_get(s); EXPECT_TRUE(cl->from == 999); EXPECT_TRUE(cl->length == 888); EXPECT_TRUE(cl->bit_pos == 777);
  cl = bclstack_get(s); EXPECT_TRUE(cl->from == 0); EXPECT_TRUE(cl->length == 5); EXPECT_TRUE(cl->bit_pos == 0);
  EXPECT_TRUE(bclstack_get(s) == NULL);

  EXPECT_TRUE(bclstack_length(s) == 0);
  EXPECT_TRUE(bclstack_empty(s));

  bclstack_free(&s);

  return 1;
}
