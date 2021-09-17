/**
  Copyright (c) 2021 Vicente Romero Calero. All rights reserved.
  Licensed under the MIT License.
  See LICENSE file in the project root for full license information.
 */
#include "unit_tests.h"
#include "../../stack.h"

struct StackItem {
  int n;
  char c;
};

CREATE_STACK(stack, struct StackItem, 10)

int test_stack_init(void)
{
  struct stack s;

  stack_init(&s);

  EXPECT_TRUE(stack_empty(&s));
  EXPECT_TRUE(stack_size(&s) == 0);

  return 1;
}

int test_stack_push_and_pop(void)
{
  struct stack s;
  struct StackItem *item;

  stack_init(&s);

  stack_push(&s, &(struct StackItem){0, 'a'});
  stack_push(&s, &(struct StackItem){1, 'b'});
  stack_push(&s, &(struct StackItem){2, 'c'});

  EXPECT_TRUE(stack_size(&s) == 3);

  item = stack_pop(&s); EXPECT_TRUE(item->n == 2 && item->c == 'c');
  item = stack_pop(&s); EXPECT_TRUE(item->n == 1 && item->c == 'b');

  EXPECT_TRUE(stack_size(&s) == 1);

  stack_push(&s, &(struct StackItem){3, 'd'});
  stack_push(&s, &(struct StackItem){4, 'e'});

  EXPECT_TRUE(stack_size(&s) == 3);

  item = stack_pop(&s); EXPECT_TRUE(item->n == 4 && item->c == 'e');
  item = stack_pop(&s); EXPECT_TRUE(item->n == 3 && item->c == 'd');
  item = stack_pop(&s); EXPECT_TRUE(item->n == 0 && item->c == 'a');

  EXPECT_TRUE(stack_size(&s) == 0);
  EXPECT_TRUE(stack_empty(&s));

  return 1;
}
