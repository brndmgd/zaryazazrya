#include "list.h"
#include <assert.h>
#include <stdio.h>

void add_in_begin_test() {
  node *begin = NULL;

  add_in_begin(&begin, 1);
  print_list(begin);

  int res = begin->data;
  assert(begin->data == 1);
}

void add_in_end_test() {
  node *begin = NULL;

  add_in_begin(&begin, 2);

  add_in_end(&begin, 3);
  print_list(begin);

  int res = begin->next->data;
  assert(res == 3);
}

void add_by_index_test() {
  node *begin = NULL;

  add_in_begin(&begin, 1);
  add_in_end(&begin, 3);

  add_by_index(&begin, 2, 1);
  print_list(begin);

  int res = begin->next->data;
  assert(res == 2);
}

void delete_by_element_test() {
  node *begin = NULL;

  add_in_begin(&begin, 1);
  add_in_end(&begin, 3);
  add_by_index(&begin, 2, 1);

  delete_by_element(&begin, 1);
  print_list(begin);

  int res = begin->data;
  assert(res == 2);
}

void delete_by_index_test() {
  node *begin = NULL;

  add_in_begin(&begin, 1);
  add_in_end(&begin, 3);
  add_by_index(&begin, 2, 0);

  delete_by_index(&begin, 0);
  print_list(begin);

  int res = begin->data;
  assert(res == 2);
}

void search_element_test() {
  node *begin = NULL;

  add_in_begin(&begin, 1);
  add_in_end(&begin, 3);
  add_by_index(&begin, 2, 1);

  int current = search_element(begin, 1);

  assert(current == 2);
}

void count_test() {
  node *begin = NULL;

  add_in_begin(&begin, 1);
  add_in_end(&begin, 3);
  add_by_index(&begin, 2, 1);

  int number = count(begin);

  assert(number == 3);
}

int main() {
  add_in_begin_test();
  add_in_end_test();
  add_by_index_test();
  delete_by_element_test();
  delete_by_index_test();
  search_element_test();
  count_test();

  return 0;
}
