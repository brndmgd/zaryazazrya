#include "assert.h"
#include "linear_allocator.h"

void linear_allocator_init_test() {
  linear_allocator *allocator_1 = linear_allocator_init(100);

  assert(allocator_1 != NULL);
  assert(allocator_1->size == 100);
  assert(allocator_1->used == 0);

  linear_free(allocator_1);

  linear_allocator *allocator_2 = linear_allocator_init(0);

  assert(allocator_2 == NULL);
}

void linear_alloc_int_test() {
  linear_allocator *allocator = linear_allocator_init(100);
  int *ptr = linear_alloc(allocator, sizeof(int));

  assert(ptr != NULL);

  *ptr = 1;

  assert(*ptr == 1);
  assert(allocator->used == sizeof(int));

  linear_free(allocator);
}

void linear_alloc_char_test() {
  linear_allocator *allocator = linear_allocator_init(100);
  char *ptr = linear_alloc(allocator, sizeof(char));

  assert(ptr != NULL);

  *ptr = 'a';

  assert(*ptr == 'a');
  assert(allocator->used == sizeof(char));

  linear_free(allocator);
}

void linear_reset_test() {
  linear_allocator *allocator = linear_allocator_init(100);
  int *a = linear_alloc(allocator, sizeof(int));
  linear_reset(allocator);
  int *b = linear_alloc(allocator, sizeof(int));

  assert(a == b);

  linear_free(allocator);
}

void linear_alloc_overflow_test() {
  linear_allocator *allocator = linear_allocator_init(100);
  void *ptr = linear_alloc(allocator, 101);

  assert(ptr == NULL);

  linear_free(allocator);
}

int main() {
  linear_allocator_init_test();
  linear_alloc_int_test();
  linear_alloc_char_test();
  linear_reset_test();
  linear_alloc_overflow_test();

  return 0;
}

