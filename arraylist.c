#include "arraylist.h"
#include <stdlib.h>
#include <string.h>

void arraylist_init(arraylist *list, linear_allocator *allocator,
                    size_t element_size) {
  list->allocator = allocator;
  list->element_size = element_size;
  list->capacity = 1;
  list->count = 0;
  list->data = NULL;
}

void arraylist_add(arraylist *list, const void *data, size_t index) {
  if (index > list->count || !data)
    return;

  if (!list->data) {
    list->data =
        linear_alloc(list->allocator, list->capacity * list->element_size);
    if (!list->data)
      return;
  }

  if (list->count == list->capacity) {
    size_t new_cap = list->capacity * 2;
    void *new_data =
        linear_alloc(list->allocator, new_cap * list->element_size);
    if (!new_data)
      return;

    memcpy(new_data, list->data, list->count * list->element_size);
    list->data = new_data;
    list->capacity = new_cap;
  }

  if (index < list->count) {
    void *dest = (char *)list->data + (index + 1) * list->element_size;
    void *src = (char *)list->data + index * list->element_size;
    size_t shift_size = (list->count - index) * list->element_size;
    memmove(dest, src, shift_size);
  }

  void *target = (char *)list->data + index * list->element_size;
  memcpy(target, data, list->element_size);
  list->count++;
}

void *arraylist_get(arraylist *list, size_t index) {
  if (index >= list->count)
    return NULL;
  return (char *)list->data + index * list->element_size;
}

void arraylist_del(arraylist *list, size_t index) {
  if (index >= list->count)
    return;

  if (index < list->count - 1) {
    void *dest = (char *)list->data + index * list->element_size;
    void *src = (char *)list->data + (index + 1) * list->element_size;
    size_t bytes_to_move = (list->count - index - 1) * list->element_size;
    memmove(dest, src, bytes_to_move);
  }

  list->count--;
}

void arraylist_free(arraylist *list) {
  if (list && list->allocator) {
    linear_free(list->allocator);
    list->data = NULL;
    list->count = list->capacity = list->element_size = 0;
  }
}
