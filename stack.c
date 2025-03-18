#include "stack.h"

stack *stack_init(int max_size) {
  stack *st = (stack *)malloc(sizeof(stack));
  st->size = max_size;
  st->top = 0;
  st->data = malloc(sizeof(int) * max_size);
  st->overflow = false;
  st->underflow = false;
  return st;
}

int push(stack *st, int value) {
  if (st->top >= st->size) {
    st->overflow = true;
    return STACK_OVERFLOW;
  }
  st->data[st->top] = value;
  st->top++;
  return 0;
}

int pop(stack *st) {
  if (st->top == 0) {
    st->underflow = true;
    return STACK_UNDERFLOW;
  }
  st->top--;
  return st->data[st->top];
}

int peek(stack *st) {
  if (st->top == 0) {
    st->underflow = true;
    return STACK_UNDERFLOW;
  }
  return st->data[st->top - 1];
}

bool is_empty(stack *st) {
  if (st->top == 0) {
    return true;
  } else {
    return false;
  }
}

void stack_free(stack *st) {
  free(st->data);
  free(st);
}