#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <sys/wait.h>
#define PROC_NUM 3
#define LOG_NUM 10000
#define ARRAY_SIZE sizeof(long int) *PROC_NUM *LOG_NUM
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
  long int **times = mmap(NULL, ARRAY_SIZE, PROT_READ|PROT_WRITE, MAP_SHARED, 0, 0);
  pid_t pids[PROC_NUM];
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
    } else {
      pids[p] = pid;
    }
  }

  if (!pid) {
    int i;
    do {
      gettimeofday(&curT, NULL);
      times[p][i] = diffMicroSec(startT, curT);
      i++;
    } while (times[p][i] <= RUNTIME_MS && i < LOG_NUM);
  } else {
    int status;
    for (p=0; p < PROC_NUM; p++) {
      waitpid(pids[p], &status, WUNTRACED);
    }
    for (p =1; i < LOG_NUM; i++) {
      printf("%ld,%d\n", times[p][i], p +1);
    }
  }

  return;
}
