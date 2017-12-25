#include <stdio.h>
#include <string.h> // for strcpy

int addTime( int start, int dur ) {
  int hrs = start /100 +( dur /100 ); int mins = dur %100 +( start %100 );
  int end = (( hrs +mins /60 ) %24) *100 +( mins %60 );

  char str[9];
  if ( end >= 500 && end < 1200 ) {
    strcpy( str, "morning" );
  } else if ( end >= 1200 && end < 1700 ) {
    strcpy( str, "afternoon" );
  } else if ( end >= 1700 && end < 2100 ) {
    strcpy( str, "evening" );
  } else {
    strcpy( str, "night" );
  }

  printf( "Start time is %i. Duration is %i. End time is %i in the %s.\n", \
    start, \
    dur, \
    end, \
    str
   );

  return end;
}

int main() {

  addTime( 1045, 345 );
  addTime( 800, 435 );
  addTime( 2300, 300 );

  return 0;
}
