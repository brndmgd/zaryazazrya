#include <stdio.h>

typedef struct node_ {
  int data;
  struct node_ *next;
} node;

void add_in_begin(node **, int);

void add_in_end(node **, int);

void add_by_index(node **, int, int);

void delete_by_element(node **, int);

void delete_by_index(node **, int);

int search_element(node *, int);

int count(node *);

void print_list(node *);
