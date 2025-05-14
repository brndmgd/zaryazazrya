#include "pool_allocator.h"
#include <assert.h>

void pool_initialization_test() {
  pool_allocator_t *allocator = pool_init(3, sizeof(int));
  assert(allocator != NULL);
  assert(allocator->chunk_count == 3);
  assert(allocator->memory != NULL && allocator->alloc_pointer != NULL);

  pool_deinit(allocator);
}

void pool_allocate_test() {
  pool_allocator_t *allocator = pool_init(2, sizeof(int));
  chunk_t *cur_pointer = allocator->alloc_pointer;
  chunk_t *next_pointer = cur_pointer->next;

  int *first = pool_alloc(allocator);
  assert(first != NULL);
  *first = 10;
  assert(*first == 10);
  assert(cur_pointer == (chunk_t *)first);
  assert(next_pointer == allocator->alloc_pointer);

  cur_pointer = allocator->alloc_pointer;
  int *second = pool_alloc(allocator);
  assert(second != NULL);
  *second = 20;
  assert(*second == 20);
  assert(cur_pointer == (chunk_t *)second);
  assert(allocator->alloc_pointer == NULL);

  pool_deinit(allocator);
}

void pool_no_chunks_left_test() {
  pool_allocator_t *allocator = pool_init(1, sizeof(int));

  int *first = pool_alloc(allocator);
  int *second = pool_alloc(allocator);
  assert(second == NULL);

  pool_deinit(allocator);
}

void pool_free_test() {
  pool_allocator_t *allocator = pool_init(2, sizeof(int));

  int *first = pool_alloc(allocator);
  int *second = pool_alloc(allocator);
  pool_free(allocator, second);
  assert(allocator->alloc_pointer == (chunk_t *)second);

  pool_deinit(allocator);
}

int main() {
  pool_initialization_test();
  pool_allocate_test();
  pool_no_chunks_left_test();
  pool_free_test();
}
