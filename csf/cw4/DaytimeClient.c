//
//  DaytimeClient
//
//  Created by <insert name>
//  Username: <inser username>
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <pthread.h>
#include <sys/socket.h>
#include <time.h>

#define kDAYTIMEPORT       1313
#define kMULTITIMEZONEPORT 1414

int main( int argc, char **argv ) {

  if ( !argv[1] ) {
    fprintf( stderr, "No hostname given!\n" );
    exit( EXIT_FAILURE );
  }

  int sock = socket( PF_INET, SOCK_STREAM, IPPROTO_TCP );
  if ( sock < 0 ) {
    fprintf( stderr, "Failed to create socket!\n" );
  }

  struct sockaddr_in server;
  memset( &server, 0, sizeof( server ) );

  struct hostent *host = gethostbyname( argv[1] );
  if ( !host ) {
    fprintf( stderr, "Could not find server!\n" );
    exit( EXIT_FAILURE );
  }

  memcpy( &server.sin_addr, host->h_addr, host->h_length );
  server.sin_family = AF_INET;
  server.sin_port = htons( kDAYTIMEPORT );

  if ( connect( sock, (struct sockaddr *) &server, sizeof( server ) ) < 0 ) {
    fprintf( stderr, "Failed to connect to socket!\n" );
    exit( EXIT_FAILURE );
  }

  char buffer[511];
  recv( sock, buffer, 511, MSG_WAITALL );

  printf( "%s", buffer );

  close( sock );
  return 0;
}
