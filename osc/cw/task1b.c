// Process scheduling (RR)
#include <stdio.h>
#include <stdlib.h>
#include "coursework.h"

// Shared pointers to head and tail of ready queue
struct process *readyHead = NULL, *readyTail = NULL;

// Insert process at end of ready queue
void listInsert(struct process *proc) {
  if (!readyHead) {
    readyHead = proc;
    readyTail = proc;
    return;
  }

  readyTail->oNext = proc;
  readyTail = proc;
}

// Remove item from head of ready queue
struct process *listPop() {
  struct process *temp = readyHead;
  readyHead = readyHead->oNext;
  temp->oNext = NULL;

  return temp;
}

int main(int argc, char **argv) {
  struct timeval start, end;

  // Fill ready queue with processes
  for (int i=0; i < NUMBER_OF_PROCESSES; i++) {
    listInsert(generateProcess());
  }

  int totResponse = 0, totTurnaround = 0;
  do {
    // Take next process out of the ready queue
    struct process *cur = listPop();

    int oldBurstTime = cur->iBurstTime;
    short oldState = cur->iState;
    simulateRoundRobinProcess(cur, &start, &end);

    printf("Process Id = %d, Previous Burst Time = %d, New Burst Time = %d",
      cur->iProcessId, oldBurstTime, cur->iBurstTime);

    if (oldState == NEW) {
      // Calculate and add response time if the process was new
      int response = getDifferenceInMilliSeconds(cur->oTimeCreated, start);
      totResponse += response;
      printf(", Response Time = %d", response);
    }

    if (cur->iState == FINISHED) {
      // Calculate and add turnaround time if process is finished
      int turnaround = getDifferenceInMilliSeconds(cur->oTimeCreated, end);
      totTurnaround += turnaround;
      printf(", Turn Around Time = %d", turnaround);

      // Then free it
      free(cur);

    } else {
      // If not finished, re-add to ready queue
      listInsert(cur);
    }

    printf("\n");
  } while(readyHead);

  // Output final result
  printf("Average response time = %lf\nAverage turn around time = %lf\n",
    (double) totResponse /NUMBER_OF_PROCESSES, (double) totTurnaround /NUMBER_OF_PROCESSES);

  return 0;
}
