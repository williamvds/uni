#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "list.h"
#include "ascrobbler.h"

#define c 0
#define p 1

void query_plays( char *play_file, int act, int artist_id ) {

  struct list *plays = read_list( play_file, parse_play );

  int count = 0;
  while ( plays != NULL ) {
    struct play *temp = (struct play *) plays->val;
    if ( artist_id > 0 && temp->artist_id != artist_id ) {
      plays = plays->next;
      continue;
    }

    if ( act == 0 ) {
      count += temp->playcount;
    } else {
      print_play( plays->val );
    }

    plays = plays->next;
  }

  if ( act == 0 ) {
    printf( "%d\n", count );
  }

}

int main( int argc, char **argv ) {
  if ( argc < 3 || argc > 4 ) {
    fprintf( stderr, "Invalid number of arguments!\n" );
    exit( EXIT_FAILURE );
  }

  int act = strcmp( "c", argv[2] ) == 0 ? c
    : strcmp( "p",  argv[2] ) == 0 ? p
    : -1;
  if ( act == -1 ) {
    fprintf( stderr, "Invalid action selected!\n" );
    exit( EXIT_FAILURE );
  }

  int artist_id;
  if ( argv[3] ) {
    artist_id = atoi( argv[3] );
  }
  query_plays( argv[1], act, artist_id? artist_id : 0 );

  return 0;
}
