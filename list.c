#include "list.h"
#include <stdlib.h>

node *list_create(int data) {
  node *new_node = (node *)malloc(sizeof(node));
  new_node->data = data;
  new_node->next = NULL;
  return new_node;
}

void add_in_begin(node **head, int value) {
  node *new_node = list_create(value);
  new_node->next = *head;
  *head = new_node;
}

void add_in_end(node **head, int value) {
  node *new_node = list_create(value);
  if (*head == NULL) {
    add_in_begin(head, value);
    return;
  }
  node *last = *head;
  while (last->next != NULL) {
    last = last->next;
  }
  last->next = new_node;
}

void add_by_index(node **head, int value, int index) {
  node *new_node = list_create(value);
  if (index == 0) {
    new_node->next = *head;
    *head = new_node;
    return;
  }
  node *current = *head;
  if (current != NULL) {
    for (int i = 0; i < index - 1; i++) {
      current = current->next;
    }
  }
  if (current == NULL) {
    add_in_end(head, value);
  } else {
    new_node->next = current->next;
    current->next = new_node;
  }
}

void delete_by_index(node **head, int index) {
  node *current = *head;
  node *pervious = NULL;
  if (index == 0 && current != NULL) {
    *head = current->next;
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

int search_element(node *head, int index) {
  node *current = head;
  for (int i = 0; i < index; ++i) {
    if (current != NULL) {
      current = current->next;
    }
  }
  if (current != NULL) {
    return current->data;
  } else {
    return -1;
  }
}

int count(node *head) {
  int number = 0;
  node *current = head;
  while (current != NULL) {
    number++;
    current = current->next;
  }
  return number;
}

void list_free(node *head) {
  node *current, *p;
  if (head != NULL) {
    current = head->next;
    head->next = NULL;
    while (current != NULL) {
      p = current->next;
      free(current);
      current = p;
    }
    free(head);
  }
}
