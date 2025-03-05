#include "list.h"
#include <stdio.h>
#include <stdlib.h>

void addInBeggin(node **begin, int value) {
  node *newNode = (node *)malloc(sizeof(node));
  newNode->data = value;
  newNode->next = *begin;
  *begin = newNode;
}

void addInEnd(node **begin, int value) {
  node *newNode = (node *)malloc(sizeof(node));
  newNode->data = value;
  newNode->next = NULL;
  if (*begin == NULL) {
    addInBeggin(begin, value);
    return;
  }
  node *last = *begin;
  while (last->next != NULL) {
    last = last->next;
  }
  last->next = newNode;
}

void addAfterIndex(node **begin, int value, int index) {
  node *newNode = (node *)malloc(sizeof(node));
  node *current = *begin;
  for (int i = 0; i < index; i++) {
    if (current != NULL) {
      current = current->next;
    }
  }
  if (current == NULL) {
    addInEnd(begin, value);
    return;
  }
  newNode->data = value;
  newNode->next = current->next;
  current->next = newNode;
}

void deleteElement(node **begin, int value) {
  node *current = *begin;
  node *previous = NULL;
  while (current != NULL && current->data != value) {
    previous = current;
    current = current->next;
  }
  if (current == NULL) {
    return;
  } else if (previous != NULL) {
    previous->next = current->next;
  } else {
    *begin = current->next;
  }
}

int searchElement(node *begin, int index) {
  node *current = begin;
  for (int i = 0; i < index; ++i) {
    if (current != NULL) {
      current = current->next;
    }
  }
  if (current != NULL) {
    printf("Элемент с заданным порядковым номером: %d\n", current->data);
  } else {
    printf("Элемента нету\n");
  }
  return current->data;
}

int count(node *begin) {
  int number = 0;
  node *current = begin;
  while (current != NULL) {
    number++;
    current = current->next;
  }
  printf("Количество элементов: %d\n", number);
  return number;
}

void printList(node *begin) {
  node *p = begin;
  while (p != NULL) {
    printf("%d ", p->data);
    p = p->next;
  }
  printf("\n");
}
