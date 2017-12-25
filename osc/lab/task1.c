#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#define PROC_NUM 20

void main(int argc, char **argv) {
  int procs[PROC_NUM];

  for (int i=0; i < PROC_NUM; i++) {
    pid_t pid = fork();
    if (pid < 0) {
      printf("Could not create procees\n");
      exit(1);

    } else if (pid) {
      procs[i] = pid;

    } else {
      sleep(1);
      printf("Hello from the child %i with pid %i\n", i +1, getpid() );

      return;
    }
  }

  return;
}

// Child processes print in random orders because the scheduler chooses to run them in a different order each time
// You don't see the bash command prompt when all child processes are finished because bash will print it before all processes are finished
