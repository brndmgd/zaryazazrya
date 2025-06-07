#include <stdio.h>

typedef struct node_ {
  int data;
  struct node_ *next;
} node;

node *list_create(int);

void add_in_begin(node **, int);

void add_in_end(node **, int);

void add_by_index(node **, int, int);

void delete_by_index(node **, int);

int search_element(node *, int);

int count(node *);

void list_free(node *head);
