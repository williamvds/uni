#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define NAMELEN     64
#define BUFFERSIZE  100

#define PLAYCOUNT 0
#define ARTISTID  1

struct play {
  int user_id;
  int artist_id;
  int playcount;
  struct play *next;
};

struct artist {
  int id;
  char name[NAMELEN];
  int playcount;
  struct artist *duplicate;
  struct artist *next;
};

struct artist *create_artist( int id, char name[] ) {
  struct artist *a = (struct artist *) malloc( sizeof( struct artist ) );
  if ( !a ) {
    fprintf( stderr, "Failed to allocate memory!\n" );
    return NULL;
  }

  a->id = id;
  a->playcount = 0;
  a->next = NULL;
  strcpy( a->name, name );

  return a;
}

struct artist *add_artist( struct artist *head, struct artist *newa ) {
  if ( newa == NULL )
    return head;
  newa->next = head;
  return newa;
}

// 1b
struct artist *read_artists( char *fname ){
  FILE *file = fopen( fname, "r" );
  if ( !file ) {
    return NULL;
  }

  int newID; char newName[NAMELEN];
  struct artist *head = NULL;
  char line[BUFFERSIZE];
  while ( fscanf( file, "%99[^\n]\n", line ) == 1 ){
    sscanf( line, "%d\t%65[^\n]\n", &newID, newName );
    struct artist *temp = create_artist( newID, newName );
    head = add_artist( head, temp );
  }

  fclose( file );
  return head;
}

// 1c
void print_artist( struct artist *a ) {
  if ( !a ) {
    printf( "NULL\n" );
    return;
  }

  printf("%s (%d) [%d]\n", a->name, a->id, a->playcount );
}

// 1d
void print_artists( struct artist *a ) {
  while ( a != NULL ) {
    print_artist( a );
    a = a->next;
  }
}

// 1e
void free_artists( struct artist *a ) {
  struct artist *prev;
  while ( a != NULL ) {
    prev = a;
    a = a->next;
    free( prev );
  }
}

// 2a
struct play *merge_plays( struct play *x, struct play *y ) {
  if ( !x ) {
    return y;
  } else if ( !y ) {
    return x;
  }

  struct play *temp, *head = NULL;
  struct play **indirect = &head;
  while ( x && y ) {
    if ( x->artist_id > y->artist_id ) {
      temp = y;
      y = x;
      x = temp;
    }

    *indirect = x;
    indirect = &x->next;

    x = x->next;
  }

  *indirect = x ? x : y; // Append last element

  return head;
}

struct play *sort_plays( struct play *head ) {
  if ( !head || !head->next ) {
    return head;
  }

  struct play *x = head, *y = head;
  while ( y->next && y->next->next ) {
    x = x->next;
    y = y->next->next;
  }

  y = x->next;
  x->next = NULL;
  x = head;

  return merge_plays( sort_plays(x), sort_plays(y) );
}

// 2b
struct artist *merge_artists( struct artist *x, struct artist *y, int criterion ) {
  if ( !x ) {
    return y;
  } else if ( !y ) {
    return x;
  }

  struct artist *temp, *head = NULL;
  struct artist **indirect = &head;
  while ( x && y ) {
    if ( criterion == PLAYCOUNT ? x->playcount < y->playcount : x->id > y->id ) {
      temp = y;
      y = x;
      x = temp;
    }

    *indirect = x;
    indirect = &x->next;

    x = x->next;
  }

  *indirect = x ? x : y; // Append last element

  return head;
}

struct artist *sort_artists( struct artist *head, int criterion ) {
  if ( !head || !head->next || ( criterion != PLAYCOUNT && criterion != ARTISTID && \
    fprintf( stderr, "Invalid criterion to sort artists!\n" ) )
  ) {
    return head;
  }

  struct artist *x = head, *y = head;
  while ( y->next && y->next->next ) {
    x = x->next;
    y = y->next->next;
  }

  y = x->next;
  x->next = NULL;
  x = head;

  return merge_artists( sort_artists( x, criterion ),
    sort_artists( y, criterion ),
    criterion );
}

// 2c
struct play *create_play( int id, int artist_id, int playcount ) {
  struct play *p = (struct play *) malloc( sizeof( struct play ) );
  if ( !p ) {
    fprintf( stderr, "Failed to allocate memory!\n" );
    exit( 1 );
  }
  p->user_id = id;
  p->artist_id = artist_id;
  p->playcount = playcount;

  return p;
}

struct play *add_play( struct play *head, struct play *newp ) {
  if ( newp == NULL )
    return head;
  newp->next = head;
  return newp;
}

struct play *read_plays( char *file_name ) {
  FILE *file = fopen( file_name, "r" );
  if ( file == NULL )
    return NULL;

  int userID, artistID, playCount;
  struct play *head = NULL;
  while ( fscanf( file, "%d %d %d\n", &userID, &artistID, &playCount ) != EOF ) {
    struct play *temp = create_play( userID, artistID, playCount );
    head = add_play( head, temp );
  }

  fclose( file );
  return head;
}

void free_plays( struct play *p ) {
  struct play *prev;
  while ( p != NULL ) {
    prev = p;
    p = p->next;
    free( prev );
  }
}

struct artist *update_counts( struct artist *a, struct play *p ) {
  a = sort_artists( a, ARTISTID );
  struct artist *head = a;

  p = sort_plays( p );

  while ( p && a ) {
    if ( p->artist_id > a->id ) {
      a = a->next;
      continue;
    }
    a->playcount += p->playcount;
    p = p->next;
  }

  return head;
}

// 2d
int main( int argc, char **argv ){
  if ( (argc != 4) && fprintf( stderr, "Invalid number of arguments\n" ) ) {
    exit( EXIT_FAILURE );
  }

  struct artist *aHead = read_artists( argv[2] );
  if ( !aHead ) {
    fprintf( stderr, "Failed to read artist data file!\n" );
    exit( EXIT_FAILURE );
  }

  struct play *pHead = read_plays( argv[3] );
  if ( !pHead ) {
    fprintf( stderr, "Failed to read play data file!\n" );
    exit( EXIT_FAILURE );
  }


  aHead = update_counts( aHead, pHead );
  aHead = sort_artists( aHead, PLAYCOUNT );
  for ( size_t i = 0; i < atoi( argv[1] ); i++ ) {
    print_artist( aHead );
    aHead = aHead->next;
  }

  free_plays( pHead );
  free_artists( aHead );

  return 0;
}
