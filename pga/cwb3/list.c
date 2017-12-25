#include <stdlib.h>
#include <stdio.h>
#include "list.h"

int length(struct list *head)
{
  int n = 0;
  while( head != NULL ) {
    head = head->next;
    n++;
  }
  return n;
}

struct list *add_elt(struct list *head, void *val)
{
  struct list *new;

  if( val == NULL )
    return head;

  else {
    new = (struct list*)malloc(sizeof(struct list));
    new->val = val;
    new->next = head;
    return new;
  }
}

struct list *read_list(char *file_name, void *(*parse)(char *))
{
  char buffer[LONGBUFSIZE];
  struct list *head = NULL;
  FILE *fp = fopen(file_name, "r");
  if( fp == NULL ) {
    printf("Cannot open file %s\n", file_name);
    return NULL;
  }

  // We do not need to check the return value of parse
  // because add_elt safely ignores NULL pointers added to the list.
  while( fgets(buffer, LONGBUFSIZE, fp) != NULL )
    head = add_elt( head, parse(buffer) );

  fclose( fp );
  return head;
}

void free_list(struct list *lst, void (*free_elt)(void *)) {
  struct list *tmp = NULL;
  while( lst != NULL ) {
    tmp = lst;
    lst = lst->next;
    free_elt(tmp->val);
    free(tmp);
  }
}

void for_each(struct list *head, void (*fun)(void *))
{
  while( head != NULL) {
    fun( head->val );
    head = head->next;
  }
}

void print_n(int n, struct list *head, void (*fun)(void *))
{
  while( head != NULL && n-- > 0 ) {
    fun(head->val);
    head = head->next;
  }
}
