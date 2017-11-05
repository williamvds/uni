// Process scheduling - shortest job first
#include <stdio.h>
#include <stdlib.h>
#include "coursework.h"
#define PROC_NUM 5

struct timeval time;

// Insert process in order of ascending duration
void listInsert(struct process **head, struct process *proc) {
  // If no head or head is >=, replace it
  if (*head == NULL || (*head)->iBurstTime >= proc->iBurstTime) {
    proc->oNext = *head;
    *head = proc;
    return;
  }

  // Loop until end or current has greater iBurstTime
  struct process *prev = NULL, *cur = *head;
  while ( cur && (cur)->iBurstTime < proc->iBurstTime) {
    prev = cur;
    cur = cur->oNext;
  }

  // Insert between current and previous link
  proc->oNext = cur;
  prev->oNext = proc;
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

  do {
    oldBurstTime = head->iBurstTime;
    simulateSJFProcess(head, start, end);

    response = getDifferenceInMilliSeconds(*init, *start);
    totResponse += response;

    turnaround = getDifferenceInMilliSeconds(*start, *end);
    totTurnaround += turnaround;

    printf("Process Id = %d, Previous Burst Time = %d, New Burst Time = %d, Response Time = %li, Turn Around Time = %li\n",
      head->iProcessId, oldBurstTime, head->iBurstTime,
      response, turnaround);
  } while((head = head->oNext));

  printf("Average response time = %lf\nAverage turn around time = %lf\n",
    totResponse /NUMBER_OF_PROCESSES, totTurnaround /NUMBER_OF_PROCESSES);
  return 0;
}
