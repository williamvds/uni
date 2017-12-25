#ifndef SORT_H
#define SORT_H

struct list *sort(struct list *x, int (*comp)(void *a, void *b));
struct list *divide(struct list *x);
struct list *merge(struct list *x, struct list *y, int (*comp)(void *a, void *b));

#endif
