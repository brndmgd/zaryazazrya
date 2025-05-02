#include "linear_allocator.h"
#include <stdlib.h>

linear_allocator *linear_allocator_init(size_t size) {
  if (size == 0)
    return NULL;

  linear_allocator *allocator = malloc(sizeof(linear_allocator));
  if (!allocator)
    return NULL;

  allocator->block_memory = malloc(size);
  if (!allocator->block_memory) {
    free(allocator);
    return NULL;
  }

  allocator->size = size;
  allocator->used = 0;

  return allocator;
}

void *linear_alloc(linear_allocator *allocator, size_t size) {
  if (!allocator || size == 0)
    return NULL;
  if (allocator->used + size > allocator->size)
    return NULL;

  void *ptr = (char *)allocator->block_memory + allocator->used;
  allocator->used += size;
  return ptr;
}

void linear_free(linear_allocator *allocator) {
  if (allocator) {
    free(allocator->block_memory);
    free(allocator);
  }
}
