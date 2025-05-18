#include <stddef.h>
#include <stdlib.h>

typedef struct {
  void *block_memory;
  size_t size;
  size_t used;
} linear_allocator;

linear_allocator *linear_allocator_init(size_t size);

void *linear_alloc(linear_allocator *allocator, size_t size);

void linear_reset(linear_allocator *allocator);

void linear_free(linear_allocator *allocator);

