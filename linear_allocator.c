#include "linear_allocator.h"

linear_allocator *linear_allocator_init(size_t size) {
  if (size == 0) {
    return NULL;
  }
  linear_allocator *allocator = malloc(sizeof(linear_allocator));
  allocator->block_memory = malloc(size);
  allocator->size = size;
  allocator->used = 0;
  return allocator;
}

void *linear_alloc(linear_allocator *allocator, size_t size) {
  if (size == 0 || allocator == NULL) {
    return NULL;
  }
  if (allocator->used + size > allocator->size) {
    return NULL;
  }
  void *current = allocator->block_memory + allocator->used;
  allocator->used += size;
  return current;
}

void linear_reset(linear_allocator *allocator) {
  if (allocator == NULL) {
    return;
  }
  allocator->used = 0;
}

void linear_free(linear_allocator *allocator) {
  if (allocator == NULL) {
    return;
  }
  free(allocator->block_memory);
  free(allocator);
}
