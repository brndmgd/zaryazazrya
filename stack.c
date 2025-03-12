#include "stack.h"

stack *stack_init(int max_size) {
  stack *st = (stack *)malloc(sizeof(stack));
  st->data = malloc(sizeof(int) * max_size);
  st->max_size = max_size;
  st->size = 0;
  st->overflow = false;
  st->underflow = false;
  return st;
}

int push(stack *st, int value) {
  if (st->size >= st->max_size) {
    st->overflow = true;
    return STACK_OVERFLOW;
  }
  st->data[st->size] = value;
  st->size++;
  return 0;
}

int pop(stack *st) {
  if (st->size == 0) {
    st->underflow = true;
    return STACK_UNDERFLOW;
  }
  st->size--;
  return st->data[st->size];
}

int peek(stack *st) {
  if (st->size == 0) {
    st->underflow = true;
    return STACK_UNDERFLOW;
  }
  return st->data[st->size - 1];
}

bool is_empty(stack *st) {
  if (st->size == 0) {
    return true;
  } else {
    return false;
  }
}
