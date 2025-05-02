#include "arraylist.h"
#include <stdlib.h>

void arraylist_init(arraylist *list, linear_allocator *allocator) {
  list->allocator = allocator;
  list->capacity = 1;
  list->count = 0;
  list->data = NULL;
}

void arraylist_add(arraylist *list, void *data, size_t index) {
  if (index > list->count)
    return;

  if (!list->data) {
    list->data = linear_alloc(list->allocator, list->capacity * sizeof(void *));
    if (!list->data)
      return;
  }

  if (list->count == list->capacity) {
    size_t new_cap = list->capacity * 2;
    void **new_data = linear_alloc(list->allocator, new_cap * sizeof(void *));
    if (!new_data)
      return;

    for (size_t i = 0; i < list->count; i++)
      new_data[i] = list->data[i];

    list->data = new_data;
    list->capacity = new_cap;
  }

  if (index != list->count) {
    for (size_t i = list->count; i > index; i--)
      list->data[i] = list->data[i - 1];
  }
  list->data[index] = data;
  list->count++;
}

void *arraylist_get(arraylist *list, size_t index) {
  return (index < list->count) ? list->data[index] : NULL;
}

void arraylist_del(arraylist *list, size_t index) {
  if (index >= list->count)
    return;

  if (index != list->count - 1) {
    for (size_t i = index; i < list->count - 1; i++)
      list->data[i] = list->data[i + 1];
  }
  list->count--;
}

void arraylist_free(arraylist *list) {
  if (list) {
    if (list->allocator) {
      linear_free(list->allocator);
      list->allocator = NULL;
    }
    list->data = NULL;
    list->count = 0;
    list->capacity = 0;
  }
}
