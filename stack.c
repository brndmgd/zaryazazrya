#include "stack.h"

stack *stack_init(int max_size) {
  stack *st = (stack *)malloc(sizeof(stack));
  st->size = max_size;
  st->top = 0;
  st->data = malloc(sizeof(int) * max_size);
  return st;
}

int push(stack *st, int value) {
  if (st->top >= st->size) {
    return STACK_OVERFLOW;
  }
  st->data[st->top] = value;
  st->top++;
  return SUCCESS;
}

int pop(stack *st, int *res) {
  if (st->top == 0) {
    return STACK_UNDERFLOW;
  }
  st->top--;
  *res = st->data[st->top];
  return SUCCESS;
}

int peek(stack *st, int *res) {
  if (st->top == 0) {
    return STACK_UNDERFLOW;
  }
  *res = st->data[st->top - 1];
  return SUCCESS;
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
