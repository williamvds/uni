#include <unistd.h> // TODO not included in example
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h> // TODO not included in example
#include <sys/wait.h> // TODO not included in example
#define PROC_NUM 5

void main(int argc, char **argv) {
  int procs[PROC_NUM];

  for (int i=0; i < PROC_NUM; i++) {
    // TODO i in example unused
    printf("Hello from the parent process\n");
    pid_t pid = fork();
    if (pid < 0) {
      printf("fork error\n");
      exit(1);

    } else if (!pid) { // TODO Should it be created before or after the others?
      sleep(1);
      printf("Hello from child process %i with pid %i\n", i, getpid() );
      return;

    } else {
      procs[i] = pid;
    }
  }

  for (int i=0; i < PROC_NUM; i++) {
    int status;
    waitpid(procs[i], &status, WUNTRACED);
  }
  printf("Bye from parent\n");

  return;
}
