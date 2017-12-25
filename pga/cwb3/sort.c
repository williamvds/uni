#include <stdlib.h>
#include <stdio.h>
#include "sort.h"
#include "list.h"

struct list *divide(struct list *x)
{

  struct list *y = x;
  while ( y->next && y->next->next ) {
    x = x->next;
    y = y->next->next;
  }

  y = x->next;
  x->next = NULL;

  return y;
}


struct list *merge(struct list *x, struct list *y, int (*comp)(void *a, void *b))
{

  struct list *tmp  = NULL;
  struct list *head = x? x : y;
  struct list **indirect = &head;

  while( x && y ) {

    // Swap x and y if x is not largest.
    if( comp(y->val, x->val) ) {
    	tmp = y;
    	y   = x;
    	x   = tmp;
    }

    *indirect = x;
    indirect = &x->next;

    x = x->next;
  }

  *indirect = x ? x : y; // Append last element


  // printf("%d\n\n", length( head ) );
//
// printf("\n\n\n" );
  return head;
}

struct list *sort(struct list *x, int (*comp)(void *a, void *b))
{
  struct list *y = NULL;
  if ( x == NULL || x->next == NULL )
    return x;

  y = divide(x);
  return merge( sort(x, comp),
		sort(y, comp),
		comp );
}
