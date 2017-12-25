#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "list.h"
#include "sort.h"
#include "ascrobbler.h"
#include "sort_artists.h"

void print_artists( struct list *a ) {
  while ( a != NULL ) {
    print_artist( a->val );
    a = a->next;
  }
}

struct list *update_counts( struct list *a, struct list *p ) {
  struct list *head = a;
  struct play *tempP;
  struct artist *tempA;

  while ( p && a ) {
    tempP = (struct play *)p->val;
    tempA = (struct artist *)a->val;

    if ( tempP->artist_id > tempA->id ) {
      a = a->next;
      continue;
    }

    tempA->count += tempP->playcount;
    p = p->next;
  }

  return head;
}

int a_geq_id(void *a, void *b) {
  struct artist *artist1 = (struct artist *)a;
  struct artist *artist2 = (struct artist *)b;
  if( artist1 != NULL && artist2 != NULL )
    return artist1->id >= artist2->id;
  else
    return 0;
}

int a_leq_pc(void *a, void *b) {
  struct artist *artist1 = (struct artist *)a;
  struct artist *artist2 = (struct artist *)b;
  if( artist1 != NULL && artist2 != NULL )
    return artist1->count <= artist2->count;
  else
    return 0;
}

void sort_artists( char *artist_file, char *plays_file, int criterion ) {

  struct list *artists = read_list( artist_file, parse_artist );

  if ( criterion == inc_pc || criterion == dec_pc ) {
    struct list *plays = read_list( plays_file, parse_play );
    plays = sort( plays, a_leq_id );
    artists = update_counts( sort( artists, a_leq_id ), sort( plays, p_leq_id ) );
    artists = sort( artists, criterion == inc_pc? a_leq_pc : a_geq_pc );

  } else {
    artists = sort( artists, criterion == inc_id? a_leq_id : a_geq_id );
  }

  print_artists( artists );
}


int main( int argc, char **argv ) {
  if ( argc != 4 ) {
    fprintf( stderr, "Invalid number of arguments!\n" );
    exit( EXIT_FAILURE );
  }

  int criterion = strcmp( argv[3], "inc_pc" ) == 0 ? inc_pc
    : strcmp( argv[3], "dec_pc" ) == 0 ? dec_pc
    : strcmp( argv[3], "inc_id" ) == 0 ? inc_id
    : strcmp( argv[3], "dec_id" ) == 0 ? dec_id
    : -1;

  if ( criterion < 0 && criterion > 3 ) {
    fprintf( stderr, "Invalid criterion!\n" );
    exit( EXIT_FAILURE );
  }

  sort_artists( argv[1], argv[2], criterion );

  return 0;
}
