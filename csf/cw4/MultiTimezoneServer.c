//  MultiTimezoneClient
//
//  Created by William Vigolo da Silva
//  Username: psywv

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <unistd.h>
#include <errno.h>
#include <pthread.h>
#include <sys/socket.h>
#include <time.h>

#define kDAYTIMEPORT        1313
#define kMULTITIMEZONEPORT  1414

void *handle( void *arg ) {
  int con = *(int*) arg;
  char buffer[12] = "GMT", outBuf[512] = {0};

  int i = 0, tz = 0;
  loop:
  while ( ++i ) {

    if ( i > 1 ) {
      memset( &buffer, 0, sizeof( buffer ) );
      do {
        size_t len = read( con, buffer +strlen( buffer ), sizeof( buffer ) -strlen( buffer ) -1 );
        // printf("Read %lu %lu \"%s\"\n", len, strlen( buffer ), buffer);
        if ( strlen( buffer ) == sizeof( buffer ) -1
            && strcmp( &buffer[strlen( buffer ) -1], "\n" ) != 0 ) {
          // Don't give error if client sends too much data
          goto loop;
        } else if ( len < 1 ) {
          // printf("SERVER) Client or server closed connection\n" );
          close( con );
          return 0;
        }
      } while ( strcmp( &buffer[strlen( buffer ) -1], "\n" ) != 0 );
      // printf("SERVER) Received \"%s\"\n", buffer );

      if ( strlen( buffer ) < 3
          || strcmp( &buffer[strlen( buffer ) -2], "\r\n" ) != 0 ) {
        // In case too much data causes buffer to be smaller than expected
        // or invalid string end
        memset( &buffer, 0, sizeof( buffer ) );
      } else {
        buffer[strlen( buffer ) -2] = 0;
      }

      if ( strcmp( buffer, "CLOSE" ) == 0 ) {
        break;
      }

      tz = strcmp( buffer, "PST" ) == 0 ? -8
      : strcmp( buffer, "MST" ) == 0 ? -7
      : strcmp( buffer, "CST" ) == 0 ? -6
      : strcmp( buffer, "EST" ) == 0 ? -5
      : strcmp( buffer, "GMT" ) == 0 ? 0
      : strcmp( buffer, "CET" ) == 0 ? 1
      : strcmp( buffer, "MSK" ) == 0 ? 3
      : strcmp( buffer, "JST" ) == 0 ? 9
      : strcmp( buffer, "AEST" ) == 0 ? 10
      : 24;

      if ( tz == 24 ) {
        memset( &outBuf, 0, sizeof( outBuf ) );
        sprintf( outBuf, "ERROR\r\n" );
        // printf( "SERVER) Sent to client: \"%s\"\n", outBuf );

        write( con, outBuf, strlen( outBuf ) );
        continue;
      }

    }

    time_t t = time( NULL );
    t += 3600 * tz;
    char *tStr = ctime( &t );
    tStr[strlen(tStr) -1] = '\0';  // Remove trailing newline

    memset( &outBuf, 0, sizeof( outBuf ) );
    sprintf( outBuf, "%.499s-%.4s\r\n", tStr, buffer );
    // printf( "SERVER) Sent to client: \"%s\"\n", outBuf );
    write( con, outBuf, strlen( outBuf ) );

  }

  // printf("SERVER) Sending bye\n" );

  sprintf( outBuf, "BYE\r\n" );
  write( con, outBuf, strlen( outBuf ) );
  close( con );
  return 0;
}

int main( int argc, char **argv ) {

  int sock = socket( PF_INET, SOCK_STREAM, IPPROTO_TCP );
  if ( sock < 0 ) {
    fprintf( stderr, "Failed to create socket!\n" );
  }

  int x = 1;
  setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &x, sizeof(int));

  struct sockaddr_in serverAddr;
  memset( &serverAddr, 0, sizeof( serverAddr ) );
  serverAddr.sin_family = AF_INET;
  serverAddr.sin_port = htons( kMULTITIMEZONEPORT );
  serverAddr.sin_addr.s_addr = htonl( INADDR_ANY );

  if ( bind( sock, (struct sockaddr *) &serverAddr, sizeof( serverAddr ) ) < 0 ) {
    fprintf( stderr, "Failed to bind socket: %d\n", errno );
    return 1;
  }

  if ( listen( sock, 15 ) < 0 ) {
    fprintf( stderr, "Failed to listen to socket\n" );
    return 2;
  }

  struct sockaddr_in clientAddr;
  unsigned int len = sizeof( clientAddr );
  while ( 1 ) {

    int con = accept( sock, (struct sockaddr *) &clientAddr, &len );
    if ( con < 1 ) {
      fprintf( stderr, "Failed to accept connection: %d, %d\n", con, errno );
      continue;
    }

    pthread_t tID;
    if ( pthread_create( &tID, NULL, handle, (void *) &con ) < 0 ) {
      fprintf( stderr, "Failed to create thread to handle connection!\n" );
      exit( EXIT_FAILURE );
    }
  }

  return 0;
}
