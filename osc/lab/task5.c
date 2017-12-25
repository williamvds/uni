#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/types.h>
#define PROC_NUM 3
#define LOG_NUM 10000
#define RUNTIME_MS .1

long int diffMilliSec(struct timeval start, struct timeval end) {
  return (end.tv_sec -start.tv_sec) *1000
    +(end.tv_usec -start.tv_usec) /1000;
}

long int diffMicroSec(struct timeval start, struct timeval end) {
  return (end.tv_sec -start.tv_sec) *1000000
    +(end.tv_usec -start.tv_usec);
}

void main(int argc, char **argv) {

  struct timeval startT, curT;
  gettimeofday(&startT, NULL);
  int p = 0;
  pid_t pid;
  for (; p < PROC_NUM; p++) {
    pid = fork();

    if (pid < 0) {
      printf("fork error\n");
      exit(1);

    } else if (!pid) {
      break; // break in child
    }
  }

  if (pid) return;

  unsigned long int times[LOG_NUM] = {0};
  int i;
  do {
    gettimeofday(&curT, NULL);
    times[i] = diffMicroSec(startT, curT);
    /* if (times[i] >10000) */
    /*   printf("%ld,%d\n", times[i], p +1); */
    i++;
  } while (times[i] <= RUNTIME_MS && i < LOG_NUM);

  for (i=1; i < LOG_NUM; i++) {
    printf("%ld,%d\n", times[i], p +1);
  }

  return;
}
