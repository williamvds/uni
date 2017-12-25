
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "list.h"
#include "sort.h"
#include "ascrobbler.h"
#include "sort_artists.h"

int comp_ints( void *a, void *b ) {
  return *(int *) a > *(int *) b;
}

int main( int argc, char **argv ) {
  int n = 0;
  struct list *artists = NULL;
  struct list *plays = NULL;
  struct artist **index = NULL;

  if( argc != 3 ) {
    printf("USAGE: recommend artists_file plays_file\n");
    exit( EXIT_FAILURE );
  }

  // fprintf(stderr, "Initialising data structures...\n");
  // fprintf(stderr, " - reading artists\t(step 1/7)\n");
  artists = read_list(argv[1], parse_artist);

  // fprintf(stderr, " - reading plays\t(step 2/7)\n");
  plays = read_list(argv[2], parse_play);

  // fprintf(stderr, " - counting artists\t(step 3/7)\n");
  n = length(artists);

  // fprintf(stderr, " - sorting plays\t(step 4/7)\n");
  plays = sort(plays, p_leq_uid_geq_count);

  // fprintf(stderr, " - sorting artists\t(step 5/7)\n");
  artists = sort(artists, a_leq_id);

  // fprintf(stderr, " - indexing artists\t(step 6/7)\n");
  index = create_index(artists, n);

  // fprintf(stderr, " - registering fans\t(step 7/7)\n");
  register_fans(index, n, plays);

  fprintf( stderr, "Enter an artist ID or 0 to quit: " );

  int artist_id = 1;
  while ( scanf( "%d", &artist_id ) == 1 && artist_id != 0 ){

    struct artist *a = lookup_artist( index, n, artist_id );
    if ( !a ) {
      fprintf( stderr, "Enter an artist ID or 0 to quit: " );
      continue;
    }

    artists = sort_similarity( a, artists );

    fprintf( stderr, "\nSimilar artists to %s:\n", a->name );

    for ( int i = 1; i <= 25; i++ ) {
      artists = artists->next;
      struct artist *temp = (struct artist *) artists->val;
      printf( "%d. %s [%d] (%.1f%%)\n", i, temp->name, temp->id, temp->similarity *100 );
    }

    fprintf( stderr, "\nEnter an artist ID or 0 to quit: " );
  }

  free_list( artists, free );
  free_list( plays, free );
  free_index( index );

}
