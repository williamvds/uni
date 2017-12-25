#include <time.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "list.h"
#include "sort.h"
#include "ascrobbler.h"

int a_geq_pc(void *a, void *b)
{
  struct artist *artist1 = (struct artist *)a;
  struct artist *artist2 = (struct artist *)b;
  if( artist1 != NULL && artist2 != NULL )
    return artist1->count >= artist2->count;
  else
    return 0;
}

int a_leq_id(void *a, void *b)
{
  struct artist *artist1 = (struct artist *)a;
  struct artist *artist2 = (struct artist *)b;
  if( artist1 != NULL && artist2 != NULL )
    return artist1->id <= artist2->id;
  else
    return 0;
}

int a_leq_jc(void *a, void *b)
{
  struct artist *artist1 = (struct artist *)a;
  struct artist *artist2 = (struct artist *)b;
  if( artist1 != NULL && artist2 != NULL )
    return artist1->similarity >= artist2->similarity;
  else
    return 0;
}

int p_leq_id(void *a, void *b)
{
  struct play *play1 = (struct play *)a;
  struct play *play2 = (struct play *)b;
  if( play1 != NULL && play2 != NULL )
    return play1->artist_id <= play2->artist_id;
  else
    return 0;
}

int p_leq_uid(void *a, void *b)
{
  struct play *play1 = (struct play *)a;
  struct play *play2 = (struct play *)b;
  if( play1 != NULL && play2 != NULL )
    return play1->user_id <= play2->user_id;
  else
    return 0;
}

int p_leq_uid_geq_count(void *a, void *b) {
  struct play *x = (struct play *)a;
  struct play *y = (struct play *)b;
  if( x->user_id == y->user_id )
    return x->playcount >= y->playcount;
  else
    return x->user_id <= y->user_id;
}

void print_play(void *elt) {
  struct play *p = (struct play *)elt;

  if( p != NULL )
    printf("user: %d artist: %d count: %d\n",
	   p->user_id,
	   p->artist_id,
	   p->playcount);
  else
    printf("NULL\n");
}

void print_artist(void *elt) {
  struct artist *a = (struct artist *)elt;
  if( a != NULL )
    printf("%s (%d) [%d] \n",
	   a->name,
	   a->id,
	   a->count);
  else
    printf("NULL\n");
}

struct play *create_play(int id, int artist_id, int playcount) {
  struct play *p = (struct play *)malloc(sizeof(struct play));
  if( p != NULL ) {
    p->user_id = id;
    p->artist_id = artist_id;
    p->playcount = playcount;
  }
  return p;
}

void free_play(struct play *p) {
  if( p != NULL )
    free(p);
}

struct artist *create_artist(int id, char *name, int count) {
  struct artist *a = (struct artist *)malloc(sizeof(struct artist));
  if( a != NULL ) {
    a->id = id;
    strcpy(a->name, name);
    a->count = count;
    a->similarity = 0;
  }

  return a;
}

void *parse_play(char *line)
{
  int u, a, c;
  if( sscanf(line, "%d %d %d\n", &u, &a, &c) == 3 )
    return (void *)create_play(u,a,c);
  else {
    return NULL;
  }
}

void *parse_artist(char *line)
{
  int id;
  char name[NAMELEN];
  if( sscanf(line, "%d\t%63[^\t\n]\n", &id, name) == 2 )
    return (void *)create_artist(id,name,0);
  else {
    return NULL;
  }
}

struct artist **create_index(struct list *head, int n) {
  int i = 0;
  struct artist **index = NULL;
  index = (struct artist **)malloc(n*sizeof(struct artist *));

  if( index != NULL )
    for(i=0; i<n && head != NULL; i++, head=head->next) {
      index[i] = (struct artist *)head->val;
    }

  return index;
}

struct artist *lookup_artist(struct artist **index, int n, int artist_id) {
  int top = 0, bot = n -1, mid;

  while ( bot -top >= 0 ) {
    mid = top +(bot -top) /2;
    if ( index[mid]->id == artist_id ) {
      return index[mid];
    } else if ( index[mid]->id < artist_id ) {
      top = mid +1;
    } else {
      bot = mid -1;
    }
  }

  return NULL;
}

void register_fan(struct artist *a, struct play *p) {
  if( a != NULL && p != NULL ) {
    a->count += p->playcount;
    a->fans = add_elt(a->fans, p);
  }
}

void register_fans(struct artist **index, int n, struct list *plays)
{
  struct play *p = NULL;
  struct artist *a = NULL;
  struct list *curr = NULL;
  int prev_id = 0;
  int pc = 0;
  int i = 0;

  for(curr = plays; curr != NULL; curr = curr->next ) {
    p = (struct play *)curr->val;

    if( p != NULL ) {
      if( prev_id != p->user_id ) {
      	pc = 0;
      	prev_id = p->user_id;
      }
      a = lookup_artist(index, n, p->artist_id);

      if( a != NULL ) {
      	if( pc < 100 )
      	  register_fan(a,p);
      	else
      	  a->count += p->playcount;
      }
      pc++;
    }
  }

  for(i=0; i<n; i++)
    if( index[i] != NULL )
      index[i]->fans = sort(index[i]->fans, p_leq_uid);

}

float similarity(struct artist *a, struct artist *b)
{
  struct list *x = a->fans;
  struct list *y = b->fans;
  int x_n = 0;
  int y_n = 0;
  int isect = 0;
  struct play *x_p = NULL;
  struct play *y_p = NULL;
  while( x != NULL || y != NULL ) {
    if( x == NULL ) {
      y_n += 1;
      y = y->next;
    } else if( y == NULL ) {
      x_n += 1;
      x = x->next;
    } else {
      x_p = (struct play *)x->val;
      y_p = (struct play *)y->val;
      if( x_p != NULL && y_p != NULL ) {
      	if( x_p->user_id == y_p->user_id ) {
      	  isect++;
      	  x_n++;
      	  y_n++;
      	  x = x->next;
      	  y = y->next;
      	} else if( x_p->user_id < y_p->user_id ) {
      	  x_n++;
      	  x = x->next;
      	} else {
      	  y_n++;
      	  y = y->next;
      	}
      } else {
      	x = x->next;
      	y = y->next;
      }
    }
  }

  return 1.0 * isect / ( x_n + y_n - isect);
}

int a_sim_geq( void *a, void *b ) {

  return ((struct artist *) a)->similarity > ((struct artist *) b)->similarity;
}

struct list *sort_similarity(struct artist *a, struct list *artists) {
  artists = sort( artists, a_geq_pc );

  struct list *tempL = artists;
  while ( tempL ) {
    struct artist *tempA = (struct artist *) tempL->val;
    if ( tempA->count < 1500 ) {
      break;
    }

    float sim = similarity( a, tempA );
    tempA->similarity = sim;

    tempL = tempL->next;
  }

  return sort( artists, a_sim_geq );
}

void free_index(struct artist **index) {
  free(index);
}
