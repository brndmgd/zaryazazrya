#include "arraylist.h"
#include <assert.h>
#include <string.h>

void test_arraylist_init() {
  linear_allocator *alloc = linear_allocator_init(64);
  arraylist list;
  arraylist_init(&list, alloc, sizeof(int));
  assert(list.count == 0);
  assert(list.capacity == 1);
  assert(list.element_size == sizeof(int));
  arraylist_free(&list);
}

void test_arraylist_add_int() {
  linear_allocator *alloc = linear_allocator_init(128);
  arraylist list;
  arraylist_init(&list, alloc, sizeof(int));
  int a = 10, b = 20;
  arraylist_add(&list, &a, 0);
  arraylist_add(&list, &b, 1);

  assert(*(int *)arraylist_get(&list, 0) == 10 &&
         *(int *)arraylist_get(&list, 1) == 20);

  arraylist_free(&list);
}

void test_arraylist_add_char() {
  linear_allocator *alloc = linear_allocator_init(128);
  arraylist list;
  arraylist_init(&list, alloc, sizeof(char));
  char a = 'a', b = 'b';
  arraylist_add(&list, &a, 0);
  arraylist_add(&list, &b, 1);

  assert(*(char *)arraylist_get(&list, 0) == 'a' &&
         *(char *)arraylist_get(&list, 1) == 'b');

  arraylist_free(&list);
}

void test_arraylist_get_int() {
  linear_allocator *alloc = linear_allocator_init(64);
  arraylist list;
  arraylist_init(&list, alloc, sizeof(int));
  int a = 52;
  arraylist_add(&list, &a, 0);

  assert(*(int *)arraylist_get(&list, 0) == 52);
  assert(arraylist_get(&list, 1) == NULL);

  arraylist_free(&list);
}

void test_arraylist_get_char() {
  linear_allocator *alloc = linear_allocator_init(64);
  arraylist list;
  arraylist_init(&list, alloc, sizeof(char));
  char c = 'c';
  arraylist_add(&list, &c, 0);

  assert(*(char *)arraylist_get(&list, 0) == 'c');
  assert(arraylist_get(&list, 2) == NULL);

  arraylist_free(&list);
}

void test_arraylist_del_int() {
  linear_allocator *alloc = linear_allocator_init(128);
  arraylist list;
  arraylist_init(&list, alloc, sizeof(int));
  int a = 10, b = 20;
  arraylist_add(&list, &a, 0);
  arraylist_add(&list, &b, 1);
  arraylist_del(&list, 0);

  assert(*(int *)arraylist_get(&list, 0) == 20 && list.count == 1);

  arraylist_free(&list);
}

void test_arraylist_del_char() {
  linear_allocator *alloc = linear_allocator_init(128);
  arraylist list;
  arraylist_init(&list, alloc, sizeof(char));
  int a = 'a', b = 'b';
  arraylist_add(&list, &a, 0);
  arraylist_add(&list, &b, 1);
  arraylist_del(&list, 0);

  assert(*(char *)arraylist_get(&list, 0) == 'b' && list.count == 1);

  arraylist_free(&list);
}

void test_arraylist_regression() {
  linear_allocator *alloc = linear_allocator_init(256);
  arraylist list;
  arraylist_init(&list, alloc, sizeof(int));

  int a = 52;
  arraylist_add(&list, &a, 0);
  void *saved_ptr = arraylist_get(&list, 0);

  arraylist_free(&list);

  assert(arraylist_get(&list, 0) == NULL);
}

int main() {
  test_arraylist_init();
  test_arraylist_add_int();
  test_arraylist_add_char();
  test_arraylist_get_int();
  test_arraylist_get_char();
  test_arraylist_del_int();
  test_arraylist_del_char();
  test_arraylist_regression();

  return 0;
}

