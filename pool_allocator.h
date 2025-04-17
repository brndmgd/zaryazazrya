#include <stdlib.h>

typedef struct {
  struct chunk_t *next;
} chunk_t;

typedef struct {
  size_t chunk_count;
  chunk_t *alloc_pointer;
  void *memory;
} pool_allocator_t;

pool_allocator_t *pool_init(size_t n_of_chunks, size_t size_of_chunk);

void pool_deinit(pool_allocator_t *allocator);

void *pool_alloc(pool_allocator_t *allocator);

void pool_free(pool_allocator_t *allocator, void *pointer);