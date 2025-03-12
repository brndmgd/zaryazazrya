#include <stdbool.h>
#include <stdlib.h>

typedef struct {
  size_t max_size;
  int *data;
  size_t size;
  bool overflow;
  bool underflow;
} stack;

stack *stack_init(int);

int push(stack *, int);

int pop(stack *);

int peek(stack *);

bool is_empty(stack *);
