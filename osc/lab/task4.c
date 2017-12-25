#include <stdio.h>
#include <stdlib.h> // TODO not included in example
#include <unistd.h> // TODO not included in example
#include <sys/time.h>
#include <sys/types.h> // TODO not included in example
#define PROC_NUM 5

long int diffMilliSec( struct timeval start, struct timeval end ) {
  return (end.tv_sec -start.tv_sec) *1000
    +(end.tv_usec -start.tv_usec) /1000;
}

long int diffMicroSec( struct timeval start, struct timeval end ) {
  return (end.tv_sec -start.tv_sec) *1000000
    +(end.tv_usec -start.tv_usec);
}

void main(int argc, char **argv) {

  for (int i=0; i < PROC_NUM; i++) {
    // TODO i in example unused
    struct timeval startT, currentT;
    gettimeofday(&startT, NULL);
    pid_t pid = fork();
    if (pid < 0) {
      printf("fork error\n");
      exit(1);

    } else if (!pid) { // TODO Should it be created before or after the others?
      gettimeofday(&currentT, NULL);
      printf("Hello from child process %i with pid %i at time %liµs\n", i, getpid(),
        diffMicroSec(startT, currentT) );
      return;
    }
  }

  return;
}
