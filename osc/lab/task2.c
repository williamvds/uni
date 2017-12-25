#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#define PROC_NUM 20

void main(int argc, char **argv) {
  int procs[PROC_NUM];

  for (int i=0; i < PROC_NUM +1; i++) {
    pid_t pid = fork();
    if (pid < 0) {
      printf("Could not create procees\n");
      exit(1);

    } else if (pid) {
      procs[i] = pid;

    } else if (i >= PROC_NUM) { // TODO Should it be created before or after the others?
      execl( "/bin/ps", "l", 0 );

    } else {
      sleep(1);
      printf("Hello from the child %i with pid %i\n", i +1, getpid() );

      return;
    }
  }

  return;
}

// Removing the sleep() causes none of the processes to be shown because they will have completed and exited before `ps -l` is run
