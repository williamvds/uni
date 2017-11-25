// SJF with bounded buffer and multiple consumers
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

// Enforce mutual exclusion when...
pthread_mutex_t syncReadyQueue, // manipulating ready queue
  syncConsumer; // writing to stdout and manipulating totals for response and turnaround times

void *producer(void *arg) {
  for (int i=0; i < NUMBER_OF_PROCESSES; i++) {
    struct process* proc = generateProcess();
    sem_wait(&canProduce);

    // Insert new process in ready queue
    pthread_mutex_lock(&syncReadyQueue);
      listInsert(proc);
    pthread_mutex_unlock(&syncReadyQueue);
    sem_post(&canConsume);
  }

  // Wake up consumers when finished to allow them to exit
  sem_post(&canConsume);

  return NULL;
}

int totResponse = 0, totTurnaround = 0;
void *consumer(void *arg) {
  int consumerID = *(int*) arg; // Get consumer ID from argument
  struct timeval start, end;

  while (1) {
    // Ensure there is a process available
    sem_wait(&canConsume);

    pthread_mutex_lock(&syncReadyQueue);
      // No process in ready queue = wake up next consumer and exit
      if (!readyHead) {
        pthread_mutex_unlock(&syncReadyQueue);
        sem_post(&canConsume);
        return NULL;
      }

      struct process *cur = listPop();
    pthread_mutex_unlock(&syncReadyQueue);
    sem_post(&canProduce); // New space in ready queue - post to consumer

    int oldBurstTime = cur->iBurstTime;
    simulateSJFProcess(cur, &start, &end);

    int response = getDifferenceInMilliSeconds(cur->oTimeCreated, start);
    int turnaround = getDifferenceInMilliSeconds(cur->oTimeCreated, end);

    printf("Consumer Id = %d, Process Id = %d, Previous Burst Time = %d, New Burst Time = %d, "
      "Response Time = %d, Turn Around Time = %d\n",
      consumerID, cur->iProcessId, oldBurstTime, cur->iBurstTime,
      response, turnaround);

    // add to total response and turnaround
    pthread_mutex_lock(&syncConsumer);
      totResponse += response;
      totTurnaround += turnaround;
    pthread_mutex_unlock(&syncConsumer);

    // Free current process
    free(cur);
  }

  return NULL;
}

int main(int argc, char **argv) {
  // Producer semaphore starts at BUFFER_SIZE to track empty spaces in ready queue
  sem_init(&canProduce, 0, BUFFER_SIZE);

  pthread_t producerT, consumerT[NUMBER_OF_CONSUMERS];

  // Create producer and consumer threads
  pthread_create(&producerT, NULL, &producer, NULL);
  for (int i = 0; i < NUMBER_OF_CONSUMERS; i++) {
    // Ensure correct ID is passed to new thread
    int *id = malloc(sizeof(int));
    *id = i +1;
    pthread_create(&consumerT[i], NULL, &consumer, id);
  }

  // Wait for producer and consumers
  pthread_join(producerT, NULL);
  for (int i = 0; i < NUMBER_OF_CONSUMERS; i++) {
    pthread_join(consumerT[i], NULL);
  }

  // Output final result
  printf("Average response time = %lf\nAverage turn around time = %lf\n",
    (double) totResponse /NUMBER_OF_PROCESSES, (double) totTurnaround /NUMBER_OF_PROCESSES);

  return 0;
}
