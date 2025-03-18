#include "list.h"
#include <assert.h>
#include <stdio.h>

void add_in_begin_test() {
  node *list = NULL;
  add_in_begin(&list, 1);

  assert(list->data == 1);
  list_free(list);
}

void add_in_end_test() {
  node *list = NULL;
  add_in_end(&list, 2);
  add_in_end(&list, 3);

  assert(list->next->data == 3);
  list_free(list);
}

void add_by_index_test() {
  node *list = NULL;
  add_by_index(&list, 1, 0);
  add_by_index(&list, 2, 1);

  assert(list->next->data == 2);
  list_free(list);
}

void delete_by_index_test() {
  node *list = NULL;
  add_in_begin(&list, 1);
  add_in_end(&list, 3);
  add_by_index(&list, 2, 0);
  delete_by_index(&list, 1);

  assert(list->data == 2);
  list_free(list);
}

void search_element_test() {
  node *list = NULL;
  add_in_begin(&list, 1);
  add_in_end(&list, 3);
  add_by_index(&list, 2, 1);
  int current = search_element(list, 1);

  assert(current == 2);
  list_free(list);
}

void count_test() {
  node *list = NULL;
  add_in_begin(&list, 1);
  add_in_end(&list, 3);
  add_by_index(&list, 2, 1);
  int number = count(list);

  assert(number == 3);
  list_free(list);
}

int main() {
  add_in_begin_test();
  add_in_end_test();
  add_by_index_test();
  delete_by_index_test();
  search_element_test();
  count_test();

  return 0;
}
