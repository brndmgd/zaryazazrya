#include <stddef.h>
#include <stdlib.h>

typedef struct linear_allocator {
  void *block_memory;
  size_t size;
  size_t used;
} linear_allocator;

typedef struct arraylist {
  void **data;
  size_t count;
  size_t capacity;
  linear_allocator *allocator;
} arraylist;

linear_allocator *linear_allocator_init(size_t size);
void *linear_alloc(linear_allocator *allocator, size_t size);
void linear_free(linear_allocator *allocator);

void arraylist_init(arraylist *list, linear_allocator *allocator);
void arraylist_add(arraylist *list, void *data, size_t index);
void *arraylist_get(arraylist *list, size_t index);
void arraylist_del(arraylist *list, size_t index);
void arraylist_free(arraylist *list);
