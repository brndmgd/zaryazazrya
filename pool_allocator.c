#include "pool_allocator.h"

pool_allocator_t *pool_init(size_t n_of_chunks, size_t chunk_size) {
  pool_allocator_t *allocator =
      (pool_allocator_t *)malloc(sizeof(pool_allocator_t));
  allocator->chunk_count = n_of_chunks;
  allocator->memory =
      (void *)malloc(n_of_chunks * (chunk_size + sizeof(chunk_t)));
  allocator->alloc_pointer = (chunk_t *)allocator->memory;

  chunk_t *cur_chunk = allocator->alloc_pointer;
  for (int i = 0; i < n_of_chunks - 1; i++) {
    cur_chunk->next = (chunk_t *)(cur_chunk + chunk_size);
    cur_chunk = cur_chunk->next;
  }
  cur_chunk->next = NULL;
  return allocator;
}

int pool_deinit(pool_allocator_t *allocator) {
  if (!allocator || !allocator->memory) {
    return NOT_INITIALIZED;
  }
  free(allocator->memory);
  free(allocator);
  return SUCCESS;
}

void *pool_alloc(pool_allocator_t *allocator) {
  if (!allocator->alloc_pointer) {
    return NULL;
  }
  chunk_t *alloc_chunk = allocator->alloc_pointer;
  allocator->alloc_pointer = alloc_chunk->next;
  return (void *)alloc_chunk;
}

void pool_free(pool_allocator_t *allocator, void *pointer) {
  chunk_t *free_chunk = (chunk_t *)pointer;
  free_chunk->next = allocator->alloc_pointer;
  allocator->alloc_pointer = free_chunk;
}