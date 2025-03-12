#include "list.h"
#include <stdio.h>
#include <stdlib.h>

void add_in_begin(node **begin, int value) {
  node *new_node = (node *)malloc(sizeof(node));
  new_node->data = value;
  new_node->next = *begin;
  *begin = new_node;
}

void add_in_end(node **begin, int value) {
  node *new_node = (node *)malloc(sizeof(node));
  new_node->data = value;
  new_node->next = NULL;
  if (*begin == NULL) {
    add_in_begin(begin, value);
    return;
  }
  node *last = *begin;
  while (last->next != NULL) {
    last = last->next;
  }
  last->next = new_node;
}

void add_by_index(node **begin, int value, int index) {
  node *new_node = (node *)malloc(sizeof(node));
  new_node->data = value;
  new_node->next = NULL;
  if (index == 0) {
    new_node->next = *begin;
    *begin = new_node;
    return;
  }
  node *current = *begin;
  node *pervious = NULL;
  if (current != NULL) {
    for (int i = 0; i < index - 1; i++) {
      pervious = current;
      current = current->next;
    }
  }
  if (current == NULL) {
    pervious->next = new_node;
  } else {
    new_node->next = current->next;
    current->next = new_node;
  }
}

void delete_by_element(node **begin, int value) {
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
  free(current);
}

void delete_by_index(node **begin, int index) {
  node *current = *begin;
  node *pervious = NULL;
  if (index == 0 && current != NULL) {
    *begin = current->next;
    free(current);
    return;
  }
  for (int i = 0; i < index; i++) {
    if (current != NULL) {
      pervious = current;
      current = current->next;
    }
  }
  if (current == NULL) {
    return;
  } else {
    pervious->next = current->next;
  }
  free(current);
}

int search_element(node *begin, int index) {
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
  printf("Количество элементов в списке: %d\n", number);
  return number;
}

void print_list(node *begin) {
  node *p = begin;
  while (p != NULL) {
    printf("%d ", p->data);
    p = p->next;
  }
  printf("\n");
}
