//  DaytimeServer
//
//  Created by William Vigolo da Silva
//  Username: psywv

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

#define kDAYTIMEPORT        1313
#define kMULTITIMEZONEPORT  1414

int con;
void clean( void ) {
  if ( con ) {
    close( con );
  }
}

int main( int argc, char **argv ) {
  atexit( clean );

  int sock = socket( PF_INET, SOCK_STREAM, IPPROTO_TCP );
  int t = 1;
  setsockopt( sock, SOL_SOCKET, SO_REUSEADDR, &t, sizeof( t ) );
  if ( sock < 0 ) {
    fprintf( stderr, "Failed to create socket!\n" );
  }

  struct sockaddr_in serverAddr;
  memset( &serverAddr, 0, sizeof( serverAddr ) );
  serverAddr.sin_family = AF_INET;
  serverAddr.sin_port = htons( kDAYTIMEPORT );
  serverAddr.sin_addr.s_addr = htonl( INADDR_ANY );

  if ( bind( sock, (struct sockaddr *) &serverAddr, sizeof( serverAddr ) ) < 0 ) {
    fprintf( stderr, "Failed to bind socket: %d\n", errno );
    return 1;
  }

  if ( listen( sock, 15 ) < 0 ) {
    fprintf( stderr, "Failed to listen to socket\n" );
    return 2;
  }

  printf( "Server) Listening on port %d\n", kDAYTIMEPORT );

  struct sockaddr_in clientAddr;
  unsigned int len = sizeof( clientAddr );
  while ( 1 ) {

    con = accept( sock, (struct sockaddr *) &clientAddr, &len );
    if ( con < 1 ) {
      fprintf( stderr, "Failed to accept connection: %d, %d\n", con, errno );
      return 3;
    }
    printf( "SERVER) Connection from %x:%d\n", \
    ntohl( clientAddr.sin_addr.s_addr ), ntohs( clientAddr.sin_port ) );

    time_t t;
    time( &t );
    char *tStr = ctime( &t );
    tStr[strlen(tStr) -1] = '\0';  // Remove trailing newline

    char outBuf[512];
    sprintf( outBuf, "%.500s-GMT\r\n", tStr );
    printf( "SERVER) Sent to client %d: %s\n", 2, outBuf );
    write( con, outBuf, strlen( outBuf ) );

    close( con );
  }

  return 0;
}
