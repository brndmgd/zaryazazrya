#include "arraylist.h"
#include <assert.h>

void test_arraylist_init() {
  linear_allocator *alloc = linear_allocator_init(64);
  arraylist list;
  arraylist_init(&list, alloc);
  assert(list.count == 0);
  assert(list.capacity == 1);
  arraylist_free(&list);
  linear_free(alloc);
}

void test_arraylist_add_int() {
  linear_allocator *alloc = linear_allocator_init(128);
  arraylist list;
  arraylist_init(&list, alloc);
  int a = 10, b = 20;
  arraylist_add(&list, &a, 0);
  arraylist_add(&list, &b, 1);
  assert(*(int *)arraylist_get(&list, 0) == 10);
  assert(*(int *)arraylist_get(&list, 1) == 20);
  arraylist_free(&list);
  linear_free(alloc);
}

void test_arraylist_add_char() {
  linear_allocator *alloc = linear_allocator_init(128);
  arraylist list;
  arraylist_init(&list, alloc);
  char a = 'a', b = 'b';
  arraylist_add(&list, &a, 0);
  arraylist_add(&list, &b, 1);
  assert(*(char *)arraylist_get(&list, 0) == 'a');
  assert(*(char *)arraylist_get(&list, 1) == 'b');
  arraylist_free(&list);
  linear_free(alloc);
}

void test_arraylist_get_int() {
  linear_allocator *alloc = linear_allocator_init(64);
  arraylist list;
  arraylist_init(&list, alloc);
  int x = 52;
  arraylist_add(&list, &x, 0);
  assert(*(int *)arraylist_get(&list, 0) == 52);
  assert(arraylist_get(&list, 1) == NULL);
  arraylist_free(&list);
  linear_free(alloc);
}

void test_arraylist_get_char() {
  linear_allocator *alloc = linear_allocator_init(64);
  arraylist list;
  arraylist_init(&list, alloc);
  char c = 'c';
  arraylist_add(&list, &c, 0);
  assert(*(char *)arraylist_get(&list, 0) == 'c');
  assert(arraylist_get(&list, 2) == NULL);
  arraylist_free(&list);
  linear_free(alloc);
}

void test_arraylist_del_int() {
  linear_allocator *alloc = linear_allocator_init(128);
  arraylist list;
  arraylist_init(&list, alloc);
  int a = 5, b = 6;
  arraylist_add(&list, &a, 0);
  arraylist_add(&list, &b, 1);
  arraylist_del(&list, 0);
  assert(*(int *)arraylist_get(&list, 0) == 6);
  arraylist_free(&list);
  linear_free(alloc);
}

void test_arraylist_del_char() {
  linear_allocator *alloc = linear_allocator_init(128);
  arraylist list;
  arraylist_init(&list, alloc);
  char a = 'a', b = 'b';
  arraylist_add(&list, &a, 0);
  arraylist_add(&list, &b, 1);
  assert(list.count == 2);
  arraylist_del(&list, 1);
  assert(list.count == 1);
  assert(*(char *)arraylist_get(&list, 0) == 'a');
  arraylist_free(&list);
  linear_free(alloc);
}

int main() {
  test_arraylist_init();
  test_arraylist_add_int();
  test_arraylist_add_char();
  test_arraylist_get_int();
  test_arraylist_get_char();
  test_arraylist_del_int();
  test_arraylist_del_char();
  return 0;
}
