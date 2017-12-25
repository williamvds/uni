#include <stdio.h>
#include <stdlib.h>

#include "list.h"
#include "sort.h"
#include "ascrobbler.h"
#include "find_artist.h"

void print_artists( struct list *a ) {
  while ( a != NULL ) {
    print_artist( a->val );
    a = a->next;
  }
}

void find_artist( int artist_id, char *file_name ) {
  struct list *artists = read_list( file_name, parse_artist );
  artists = sort( artists, a_leq_id );
  struct artist **index = create_index( artists, length( artists ) );
  struct artist *a = lookup_artist( index, length( artists ), artist_id );

  printf( "%s\n", a? a->name : "Not found" );
}

int main( int argc, char **argv ) {
  if ( argc != 3 ) {
    fprintf( stderr, "Invalid number of arguments!\n" );
    exit( EXIT_FAILURE );
  }

  find_artist( atoi( argv[1] ), argv[2] );

  return 0;
}
