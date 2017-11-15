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
  // Walk list until we get to the last entry
  while((*cur)->oNext)
    cur = &(*cur)->oNext;

  (*cur)->oNext = proc;
}

void listRemove(struct process **head, struct process *proc) {
  struct process **cur = head;
  // Find entry before process we want to remove
  while((*cur) != proc)
    cur = &(*cur)->oNext;

  // Replace previous' ->next with removed entry's ->next
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

  int totResponse = 0, totTurnaround = 0;
  struct process *cur = head;
  do {
    int oldBurstTime = cur->iBurstTime;
    short oldState = cur->iState;
    simulateRoundRobinProcess(cur, start, end);

    printf("Process Id = %d, Previous Burst Time = %d, New Burst Time = %d",
      cur->iProcessId, oldBurstTime, cur->iBurstTime);

    if (oldState == NEW) { // output response time if the process is new
      int response = getDifferenceInMilliSeconds(cur->oTimeCreated, *start);
      totResponse += response;
      printf(", Response Time = %d", response);
    }

    if (cur->iState == FINISHED) { // output turnaround if process is completed
      int turnaround = getDifferenceInMilliSeconds(cur->oTimeCreated, *end);
      totTurnaround += turnaround;
      printf(", Turn Around Time = %d", turnaround);

      listRemove(&head, cur); // remove completed processes
    }

    printf("\n");
  } while((cur = cur->oNext) || (cur = head)); // go to next process or loop around

  printf("Average response time = %lf\nAverage turn around time = %lf\n",
    (double) totResponse /NUMBER_OF_PROCESSES, (double) totTurnaround /NUMBER_OF_PROCESSES);

  return 0;
}
