#include "stack.h"
#include <stdbool.h>
#include <stdlib.h>
#define STACK_UNDERFLOW -100
#define STACK_OVERFLOW -101

stack *stack_init(int max_size) {
  stack *st = (stack *)malloc(sizeof(stack));
  st->data = malloc(sizeof(int) * max_size);
  st->max_size = max_size - 1;
  st->size = -1;
  return st;
}

int push(stack *st, int value) {
  if (st->size >= st->max_size) {
    return STACK_OVERFLOW;
  }
  st->size++;
  st->data[st->size] = value;
  return 0;
}

int pop(stack *st) {
  if (st->size == -1) {
    return STACK_UNDERFLOW;
  }
  int value = st->data[st->size];
  st->size--;
  return value;
}

int peek(stack *st) {
  if (st->size == -1) {
    return STACK_UNDERFLOW;
  }
  return st->data[st->size];
}

bool is_empty(stack *st) {
  if (st->size == -1) {
    return true;
  } else {
    return false;
  }
}
