#include "stack.h"
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#define STACK_UNDERFLOW -100
#define STACK_OVERFLOW -101

void stack_underflow_test() {
  stack *st = stack_init(2);
  int res = pop(st);

  assert(res == STACK_UNDERFLOW);
}

void stack_overflow_test() {
  stack *st = stack_init(2);
  push(st, 2);
  push(st, 3);
  int res = push(st, 4);

  assert(res == STACK_OVERFLOW);
}

void stack_pushpop_test() {
  stack *st = stack_init(2);
  push(st, 5);
  int res = pop(st);

  assert(res == 5);
}

void stack_empty_test() {
  stack *st = stack_init(2);
  bool res = is_empty(st);

  assert(res == true);
}

void stack_notempty_test() {
  stack *st = stack_init(2);
  push(st, 2);
  bool res = is_empty(st);

  assert(res == false);
}

int main() {

  stack_underflow_test();
  stack_overflow_test();
  stack_pushpop_test();
  stack_empty_test();
  stack_notempty_test();
  printf("stack success\n");

  return 0;
}
