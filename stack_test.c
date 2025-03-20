#include "stack.h"
#include <assert.h>
#include <stdio.h>

void stack_underflow_test() {
  stack *st = stack_init(2);
  int res = pop(st);

  assert(res == STACK_UNDERFLOW);
  stack_free(st);
}

void stack_overflow_test() {
  stack *st = stack_init(2);
  push(st, 2);
  push(st, 3);
  int res = push(st, 4);

  assert(res == STACK_OVERFLOW);
  stack_free(st);
}

void stack_push_test() {
  stack *st = stack_init(2);
  push(st, 5);
  int res = st->data[0];

  assert(res == 5);
  stack_free(st);
}

void stack_pop_test() {
  stack *st = stack_init(2);
  push(st, 5);
  int res = pop(st);

  assert(res == 5);
  stack_free(st);
}

void stack_peek_test() {
  stack *st = stack_init(2);
  push(st, 5);
  int res = peek(st);

  assert(res == 5);
  stack_free(st);
}

void stack_empty_test() {
  stack *st = stack_init(2);
  bool res = is_empty(st);

  assert(res == true);
  stack_free(st);
}

void stack_not_empty_test() {
  stack *st = stack_init(2);
  push(st, 2);
  bool res = is_empty(st);

  assert(res == false);
  stack_free(st);
}

int main() {

  stack_underflow_test();
  stack_overflow_test();
  stack_push_test();
  stack_pop_test();
  stack_peek_test();
  stack_empty_test();
  stack_not_empty_test();

  return 0;
}
