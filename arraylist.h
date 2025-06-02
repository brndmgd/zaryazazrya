#include "linear_allocator.h"
#include <stddef.h>

typedef struct arraylist {
  void *data;
  size_t count;
  size_t capacity;
  size_t element_size;
  linear_allocator *allocator;
} arraylist;

void arraylist_init(arraylist *list, linear_allocator *allocator,
                    size_t element_size);
void arraylist_add(arraylist *list, const void *data, size_t index);
void *arraylist_get(arraylist *list, size_t index);
void arraylist_del(arraylist *list, size_t index);
void arraylist_free(arraylist *list);
