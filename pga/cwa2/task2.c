#include <stdio.h>

void change( int val ) {
  int denoms[4] = {20, 10, 5, 1}; int notesCoins[4] = {0};
  int rem = val;

  int lastDenom = 0; int nonZero = 0;
  for ( size_t i= 0; i < 4; i++ ) {
    int delta = rem /denoms[i];
    notesCoins[i] = delta;
    rem = rem %denoms[i];

    if ( delta > 0 ) { lastDenom = i; nonZero++; }
  }

  int prints = 0;
  printf( "£%i consists of ", val );
  for ( size_t i= 0; i < 4; i++ ) {
    if ( notesCoins[i] < 1 ){ continue; }

    printf( "%s%s%i %s", \
      prints > 0 ? ", " : "" , \
      i == lastDenom && nonZero > 1 ? "and " : "" , \
      notesCoins[i], \
      i < 3 ? "£" : "pound" );

    if ( i < 3 ){
      printf( "%i", denoms[i] );
    }

    printf( " %s%s", \
      i < 3 ? "note" : "coin", \
      notesCoins[i] > 1 ? "s" : "" );

    prints++;
  }

  printf( ".\n" );
}

int main() {

  int vals[4] = {20, 79, 10, 45};
  for ( size_t i= 0; i < 4; i++ ) {
    change( vals[i] );
  }

  return 0;
}
