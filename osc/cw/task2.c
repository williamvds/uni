// SJF with bounded buffer
#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>
#include "coursework.h"

// Shared pointer to head of ready queue
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
struct process *listPop() {
  struct process *temp = readyHead;
  readyHead = readyHead->oNext;
  temp->oNext = NULL;

  return temp;
}

sem_t canProduce, // Track number of free spaces in ready queue
  canConsume; // Track number of processes in ready queue

// Enforce mutual exclusion when manipulating ready queue
pthread_mutex_t syncReadyQueue;

void *producer(void *arg) {
  for (int i=0; i < NUMBER_OF_PROCESSES; i++) {
    struct process* proc = generateProcess();
    sem_wait(&canProduce);

    pthread_mutex_lock(&syncReadyQueue);
      listInsert(proc);
    sem_post(&canConsume);
    pthread_mutex_unlock(&syncReadyQueue);
  }

  return NULL;
}

void *consumer(void *arg) {
  struct timeval start, end;

  int totResponse = 0, totTurnaround = 0;
  for (int i=0; i < NUMBER_OF_PROCESSES; i++) {
    // Ensure there is a process available
    sem_wait(&canConsume);

    pthread_mutex_lock(&syncReadyQueue);
      struct process *cur = listPop();
    pthread_mutex_unlock(&syncReadyQueue);

    sem_post(&canProduce); // New space in ready queue - post to consumer

    int oldBurstTime = cur->iBurstTime;
    simulateSJFProcess(cur, &start, &end);

    int response = getDifferenceInMilliSeconds(cur->oTimeCreated, start);
    totResponse += response;

    int turnaround = getDifferenceInMilliSeconds(cur->oTimeCreated, end);
    totTurnaround += turnaround;

    printf("Process Id = %d, Previous Burst Time = %d, New Burst Time = %d, Response Time = %d, "
      "Turn Around Time = %d\n",
      cur->iProcessId, oldBurstTime, cur->iBurstTime,
      response, turnaround);

    free(cur);
  }

  // Output final result
  printf("Average response time = %lf\nAverage turn around time = %lf\n",
    (double) totResponse /NUMBER_OF_PROCESSES, (double) totTurnaround /NUMBER_OF_PROCESSES);

  return NULL;
}

int main(int argc, char **argv) {
  // Producer semaphore starts at BUFFER_SIZE to track empty spaces in ready queue
  sem_init(&canProduce, 0, BUFFER_SIZE);

  pthread_t producerT, consumerT;
  // Create producer and consumer threads
  pthread_create(&producerT, NULL, &producer, NULL);
  pthread_create(&consumerT, NULL, &consumer, NULL);

  // Wait for producer and consumers
  pthread_join(producerT, NULL);
  pthread_join(consumerT, NULL);

  return 0;
}
