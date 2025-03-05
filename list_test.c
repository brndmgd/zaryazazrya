#include "list.h"
#include <assert.h>
#include <stdio.h>

void addInBeggin_test() {
  node *beggin = NULL;

  addInBeggin(&beggin, 1);
  printList(beggin);

  assert(beggin != NULL);
}

void addInEnd_test() {
  node *beggin = NULL;

  addInBeggin(&beggin, 2);
  addInBeggin(&beggin, 1);

  addInEnd(&beggin, 3);
  printList(beggin);

  assert(beggin != NULL);
}

void addAfterIndex_test() {
  node *beggin = NULL;

  addInBeggin(&beggin, 1);
  addInEnd(&beggin, 3);

  addAfterIndex(&beggin, 2, 0);
  printList(beggin);

  assert(beggin != NULL);
}

void deleteElement_test() {
  node *beggin = NULL;

  addInBeggin(&beggin, 1);
  addInEnd(&beggin, 3);
  addAfterIndex(&beggin, 2, 0);

  deleteElement(&beggin, 1);
  printList(beggin);

  assert(beggin != NULL);
}

void searchElement_test() {
  node *beggin = NULL;

  addInBeggin(&beggin, 1);
  addInEnd(&beggin, 3);
  addAfterIndex(&beggin, 2, 0);

  int current = searchElement(beggin, 0);

  assert(current == 1);
}

void count_test() {
  node *beggin = NULL;

  addInBeggin(&beggin, 1);
  addInEnd(&beggin, 3);
  addAfterIndex(&beggin, 2, 0);

  int number = count(beggin);

  assert(number == 3);
}

int main() {
  addInBeggin_test();
  addInEnd_test();
  addAfterIndex_test();
  deleteElement_test();
  searchElement_test();
  count_test();

  return 0;
}