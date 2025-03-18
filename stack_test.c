#include "stack.h"
#include <assert.h>
#include <stdio.h>

void stack_underflow_test() {
  stack *st = stack_init(2);
  int res = pop(st);

  assert(st->underflow == true && res == -2);
  stack_free(st);
}

void stack_overflow_test() {
  stack *st = stack_init(2);
  push(st, 2);
  push(st, 3);
  int res = push(st, 4);

  assert(st->overflow == true && res == -1);
  stack_free(st);
}

void stack_push_pop_test() {
  stack *st = stack_init(2);
  push(st, 5);
  int res = pop(st);

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
  stack_push_pop_test();
  stack_empty_test();
  stack_not_empty_test();

  return 0;
}
