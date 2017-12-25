#include <stdio.h>
#include <math.h>

double vol( double r ) {
  if ( r < 0 ){
    printf( "Error: given radius %g is less than 0\n", r );
    return -1;
  }

  double v = (4.0/3) *3.14159265 *pow( r, 3 );
  printf( "The volume of a sphere with radius %g is %f\n", r, v );

  return v;
}

int main() {

  double radii[5] = {1, 4.657, -.05, 10, 42};
  for ( size_t i= 0; i < 5; i++ ) {
    vol( radii[i] );
  }

  return 0;
}
