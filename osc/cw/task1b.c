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
  struct timeval *init = malloc(sizeof(struct timeval)),
    *start = malloc(sizeof(struct timeval)),
    *end = malloc(sizeof(struct timeval));

  for (int i=0; i < NUMBER_OF_PROCESSES; i++) {
    listInsert(&head, generateProcess());
  }

  int oldBurstTime;
  long int response, turnaround;
  double totResponse = 0, totTurnaround = 0;
  gettimeofday(init, NULL);

  struct process *cur = head;
  do {
    oldBurstTime = cur->iBurstTime;
    simulateRoundRobinProcess(cur, start, end);

    response = getDifferenceInMilliSeconds(*init, *start);
    totResponse += response;

    turnaround = getDifferenceInMilliSeconds(*start, *end);
    totTurnaround += turnaround;

    printf("Process Id = %d, Previous Burst Time = %d, New Burst Time = %d, Response Time = %li, "
      "Turn Around Time = %li\n",
      cur->iProcessId, oldBurstTime, cur->iBurstTime,
      response, turnaround);

    // Remove completed processes
    if (cur->iBurstTime == 0) listRemove(&head, cur);
  } while((cur = cur->oNext) || (cur = head));

  printf("Average response time = %lf\nAverage turn around time = %lf\n",
    totResponse /NUMBER_OF_PROCESSES, totTurnaround /NUMBER_OF_PROCESSES);
  return 0;
}
