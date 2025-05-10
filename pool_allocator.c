#include "pool_allocator.h"

pool_allocator_t *pool_init(size_t n_of_chunks, size_t chunk_size) {
  pool_allocator_t *allocator =
      (pool_allocator_t *)malloc(sizeof(pool_allocator_t));
  if (allocator == NULL) {
    return NULL;
  }

  allocator->chunk_count = n_of_chunks;
  allocator->memory =
      (void *)malloc(n_of_chunks * (chunk_size + sizeof(chunk_t)));
  if (allocator->memory == NULL) {
    return NULL;
  }
  allocator->alloc_pointer = (chunk_t *)allocator->memory;

  chunk_t *cur_chunk = allocator->alloc_pointer;
  for (int i = 0; i < n_of_chunks - 1; i++) {
    cur_chunk->next = (chunk_t *)(cur_chunk + chunk_size);
    cur_chunk = cur_chunk->next;
  }
  cur_chunk->next = NULL;
  return allocator;
}

void pool_deinit(pool_allocator_t *allocator) {
  if (allocator == NULL) {
    return;
  }

  if (allocator->memory != NULL) {
    free(allocator->memory);
  }

  free(allocator);
}

void *pool_alloc(pool_allocator_t *allocator) {
  if (allocator == NULL) {
    return NULL;
  }

  if (allocator->alloc_pointer == NULL) {
    return NULL;
  }

  chunk_t *alloc_chunk = allocator->alloc_pointer;
  allocator->alloc_pointer = alloc_chunk->next;
  return (void *)alloc_chunk;
}

void pool_free(pool_allocator_t *allocator, void *pointer) {
  if (allocator == NULL) {
    return;
  }

  if (pointer == NULL) {
    return;
  }

  chunk_t *free_chunk = (chunk_t *)pointer;
  free_chunk->next = allocator->alloc_pointer;
  allocator->alloc_pointer = free_chunk;
}
