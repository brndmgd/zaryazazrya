#include <stdio.h>

typedef struct node_ {
  int data;
  struct node_ *next;
} node;

void addInBeggin(node **, int);

void addInEnd(node **, int);

void addAfterIndex(node **, int, int);

void deleteElement(node **, int);

int searchElement(node *, int);

int count(node *);

void printList(node *);