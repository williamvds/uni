#include <stdio.h>

void rect( int w, int h ) {
  if ( w < 0 ) {
    printf( "Invalid value - width is negative.\n" ); return;

  } else if ( h < 0 ) {
    printf( "Invalid value - height is negative.\n" ); return;

  } else if ( w > 80 ) {
    printf( "Invalid value - %i is too wide.\n", w ); return;

  } else if ( h > 80 ) {
    printf( "Invalid value - %i is too tall.\n", h ); return;

  }

  for ( size_t i = 0; i < h; i++ ) {
    for ( size_t j = 0; j < w; j++ ) {
      putchar( '*' );
    }

    putchar( '\n' );
  }
}

int main() {

  int width = 1, height = 1;
  while (1) {
    printf( "Please enter the width and height for your rectangle " \
    "(separated by a comma, e.g. 3,4): " );

    scanf( "%d,%d", &width, &height );

    if ( width == 0 || height == 0 ){ break; }
    rect( width, height );
    putchar( '\n' );
  }

  return 0;
}
