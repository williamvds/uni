#ifndef LIST_H
#define LIST_H

#define LONGBUFSIZE 1000

struct list
{
  void *val;
  struct list *next;
};

struct list *add_elt(struct list *head, void *elt);
struct list *read_list(char *file_name, void *(*parse)(char *line));
void free_list(struct list *lst, void (*free_elt)(void *));
void for_each(struct list *head, void (*fun)(void *));
void print_n(int n, struct list *head, void (*fun)(void *));
int length(struct list *head);

#endif
