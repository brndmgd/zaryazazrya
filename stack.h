#include <stdbool.h>
#include <stdlib.h>
#define STACK_OVERFLOW -1
#define STACK_UNDERFLOW -2

typedef struct {
  size_t size;
  size_t top;
  int *data;
  bool overflow;
  bool underflow;
} stack;

stack *stack_init(int);

int push(stack *, int);

int pop(stack *);

int peek(stack *);

bool is_empty(stack *);

void stack_free(stack *);
