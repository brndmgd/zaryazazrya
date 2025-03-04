#include <stdbool.h>

typedef struct {
  int max_size;
  int *data;
  int size;
} stack;

stack *stack_init(int);

int push(stack *, int);

int pop(stack *);

int peek(stack *);

bool is_empty(stack *);
