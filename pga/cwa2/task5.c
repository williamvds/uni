#include <stdio.h>

void mandelbrot() {

  // for ( double y = -1; y <= 1; y += ( 1.0/53 ) *2.0 ) {
    // double y = -1 +(intY +1) /53.0 *2.0;
  for ( size_t intY = 53; intY > 0; intY-- ) {
    double y = -1 +(intY) /53.0 *2.0;

    // for ( double x = -1.5; x <= 1.5; x += ( 1.0/80 ) *3.0 ) {
    for ( int intX = 0; intX < 80; intX++ ) {
      double x = -1.5 +(intX +1) /80.0 *3.0;

      int it = 4096; double r; double i;
      r = i = 0; double r2 = 0; double i2 = 0;
      do {
        double tmp = r2 - i2 + x;
        i = 2 * r * i + y;
        r = tmp;
        r2 = r*r; i2 = i*i;
      } while((r2 + i2) <= 4.0 && --it );

      putchar( it == 0 ? ' ' : '*' );
    }

    putchar( '\n' );
  }


}

int main() {

  mandelbrot();

  return 0;
}
