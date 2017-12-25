//  MultiTimezoneClient
//
//  Created by William Vigolo da Silva
//  Username: psywv

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <sys/socket.h>
#include <time.h>

#define kDAYTIMEPORT       1313
#define kMULTITIMEZONEPORT 1414

int main( int argc, char **argv ) {

  if ( !argv[1] && fprintf( stderr, "No hostname given!\n" ) ) {
    exit( EXIT_FAILURE );
  }

  int sock = socket( PF_INET, SOCK_STREAM, IPPROTO_TCP );
  if ( sock < 0 ) {
    fprintf( stderr, "Failed to create socket!\n" );
    exit( EXIT_FAILURE );
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
  server.sin_port = htons( kMULTITIMEZONEPORT );

  if ( connect( sock, (struct sockaddr *) &server, sizeof( server ) ) < 0 ) {
    fprintf( stderr, "Failed to connect to socket!\n" );
    exit( EXIT_FAILURE );
  }

  char buffer[512] = {0};
  int i = 1;  // -1 to include first GMT message
  while ( i++ ) {
    memset( &buffer, 0, sizeof( buffer ) );
    while ( strcmp( &buffer[strlen( buffer ) -2], "\r\n" ) != 0 ) {
      read( sock, buffer +strlen( buffer ), sizeof( buffer ) -strlen( buffer ) -1 );
    }
    printf( "%s%c", buffer, i == argc ? '\0' : '\n' );

    if ( i == argc ) {
      break;
    }

    memset( &buffer, 0, sizeof( buffer ) );
    sprintf( buffer, "%.509s\r\n", argv[i] );
    write( sock, buffer, strlen( buffer ) );
    // printf("CLIENT) Sent \"%s\"\n", buffer );
  }

  ssize_t len =0 ;
  do {
    write( sock, "CLOSE\r\n", 8 );
    // printf("CLIENT) Sent \"CLOSE\r\n\"\n" );

    // printf("Waiting for bye %lu\n", len );
    memset( &buffer, 0, sizeof( buffer ) );
    len = read( sock, buffer, sizeof( buffer ) -1 );
    // printf("CLIENT) received \"%s\"\n", buffer );
  } while ( len > 0 && strcmp( buffer, "BYE\r\n" ) != 0 );

  close( sock );
  return 0;
}
