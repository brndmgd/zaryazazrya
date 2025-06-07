#include <stdbool.h>
#include <stdlib.h>
#define STACK_OVERFLOW -1
#define STACK_UNDERFLOW -2
#define SUCCESS 0

typedef struct {
  size_t size;
  size_t top;
  int *data;
} stack;

stack *stack_init(int);

int push(stack *, int);

int pop(stack *, int *);

int peek(stack *, int *);

bool is_empty(stack *);

void stack_free(stack *);
