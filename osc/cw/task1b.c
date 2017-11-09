// Process scheduling - round-robin
#include <stdio.h>
#include <stdlib.h>
#include "coursework.h"

// Insert process at end
void listInsert(struct process **head, struct process *proc) {
  if (!*head) {
    *head = proc;
    return;
  }

  struct process **cur = head;
  while((*cur)->oNext)
    cur = &(*cur)->oNext;

  (*cur)->oNext = proc;
}

void listRemove(struct process **head, struct process *proc) {
  struct process **cur = head;
  while((*cur) != proc)
    cur = &(*cur)->oNext;

  // Replace proc with its ->next
  *cur = proc->oNext;
  free(proc);
}

int main(int argc, char **argv) {
  struct process *head = NULL;
  struct timeval *start = malloc(sizeof(struct timeval)),
    *end = malloc(sizeof(struct timeval));

  for (int i=0; i < NUMBER_OF_PROCESSES; i++) {
    listInsert(&head, generateProcess());
  }

  int oldBurstTime, oldState;
  long int response, turnaround;
  int totResponse = 0, totTurnaround = 0;

  struct process *cur = head;
  do {
    oldBurstTime = cur->iBurstTime;
    oldState = cur->iState;
    simulateRoundRobinProcess(cur, start, end);

    printf("Process Id = %d, Previous Burst Time = %d, New Burst Time = %d",
      cur->iProcessId, oldBurstTime, cur->iBurstTime);

    if (oldState == NEW) { // only do response time if the process is new
      response = getDifferenceInMilliSeconds(cur->oTimeCreated, *start);
      totResponse += response;
      printf(", Response Time = %li", response);
    }

    if (cur->iBurstTime == 0) {
      turnaround = getDifferenceInMilliSeconds(cur->oTimeCreated, *end);
      totTurnaround += turnaround;
      printf(", Turn Around Time = %li", turnaround);

      listRemove(&head, cur); // remove completed processes
    }

    printf("\n");
  } while((cur = cur->oNext) || (cur = head));

  printf("Average response time = %lf\nAverage turn around time = %lf\n",
    (double) totResponse /NUMBER_OF_PROCESSES, (double) totTurnaround /NUMBER_OF_PROCESSES);

  return 0;
}
