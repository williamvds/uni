// Process scheduling (SJF)
#include <stdio.h>
#include <stdlib.h>
#include "coursework.h"

// Global pointer to head of ready queue
struct process *readyHead = NULL;

// Insert process in ready queue in order of ascending duration
void listInsert(struct process *proc) {
  // If no head or head is >=, replace it
  if (readyHead == NULL || readyHead->iBurstTime >= proc->iBurstTime) {
    proc->oNext = readyHead;
    readyHead = proc;
    return;
  }

  // Loop until end or current has greater iBurstTime
  struct process *prev = NULL, *cur = readyHead;
  while ( cur && (cur)->iBurstTime < proc->iBurstTime) {
    prev = cur;
    cur = cur->oNext;
  }

  // Insert between current and previous link
  proc->oNext = cur;
  prev->oNext = proc;
}

// Pop from head of list
void listPop() {
  readyHead = readyHead->oNext;
}

int main(int argc, char **argv) {
  struct timeval start, end;

  // Fill ready queue with processes
  for (int i=0; i < NUMBER_OF_PROCESSES; i++) {
    listInsert(generateProcess());
  }

  int totResponse = 0, totTurnaround = 0;
  do {
    int oldBurstTime = readyHead->iBurstTime;
    simulateSJFProcess(readyHead, &start, &end);

    int response = getDifferenceInMilliSeconds(readyHead->oTimeCreated, start);
    totResponse += response;

    int turnaround = getDifferenceInMilliSeconds(readyHead->oTimeCreated, end);
    totTurnaround += turnaround;

    printf("Process Id = %d, Previous Burst Time = %d, New Burst Time = %d, Response Time = %d, "
      "Turn Around Time = %d\n",
      readyHead->iProcessId, oldBurstTime, readyHead->iBurstTime,
      response, turnaround);

    listPop();
  } while(readyHead); // Repeat for the entire list

  // Output final result
  printf("Average response time = %lf\nAverage turn around time = %lf\n",
    (double) totResponse /NUMBER_OF_PROCESSES, (double) totTurnaround /NUMBER_OF_PROCESSES);

  return 0;
}
