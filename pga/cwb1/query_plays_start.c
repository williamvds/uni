#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NAMELEN 64
#define BUFSIZE 100

struct play {
  int user_id;
  int artist_id;
  int playcount;
  struct play *next;
};

void print_play( struct play *p ) {
  if ( p == NULL ) {
    printf( "NULL\n" );
    return;
  }
  printf( "user: %d artist: %d count: %d\n", p->user_id, p->artist_id, p->playcount );
}

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

struct play *parse_play(char *line)
{
  printf("Function play *parse_play is not yet defined.\n");
  return NULL;
}

void free_play( struct play *p ) {
  free( p );
}

struct play *add_play( struct play *head, struct play *newp ) {
  if ( newp == NULL )
    return head;
  newp->next = head;
  return newp;
}

void print_plays( struct play *p ) {
  while ( p != NULL ) {
    print_play( p );
    p = p->next;
  }
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

int count_plays( struct play *head ) {
  int tot = 0;
  while ( head != NULL ) {
    tot += head->playcount;
    head = head->next;
  }

  return tot;
}

struct play *filter_user( int user_id, struct play *head ) {
  // medium.com/@bartobri/99749f37684a
  struct play ** indirect = &head; struct play *temp;
  while ( *(indirect) != NULL ) {
    if ( (*indirect)->user_id != user_id ) {
      temp = (*indirect)->next;
      free( *indirect );
      *indirect = temp;
      continue;
    }

    indirect = &(*indirect)->next;
  }

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

void exit_usage() {
  printf("USAGE: query_plays file command\n"
         "\n"
         "where command is one of\n"
         "\n"
         "   p <userid>  prints plays, optionally limited to user.\n"
         "   c <userid>  counts plays, optionally limited to user.\n");
   exit(1);
}

void test_task1() {
  struct play *test_play = NULL;
  print_play(test_play);
  test_play = create_play(1,2,3);
  print_play(test_play);
  free_play(test_play);
}

void test_task2() {
  struct play *a = create_play(1,2,3);
  struct play *b = create_play(4,5,6);
  a = add_play(a, b);
  a = add_play(a, NULL);
  print_plays(a);
  printf("There are %d plays in a.\n", count_plays(a));
}

int main( int argc, char **argv ) {

  test_task1();
  test_task2();
  exit_usage();

}
