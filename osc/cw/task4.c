// RR with bounded buffer and multiple consumers
#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>
#include "coursework.h"

// Shared pointers to head and tail of ready queue
struct process *readyHead = NULL, *readyTail;

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

sem_t canProduce, // Track number of free spaces in ready queue
  canConsume; // Track number of processes in ready queue

// Enforce mutual exclusion when...
pthread_mutex_t syncReadyQueue, // manipulating ready queue
  syncConsumer; // writing to stdout and manipulating totals for response and turnaround times

void *producer(void *arg) {
  for (int i=0; i < NUMBER_OF_PROCESSES; i++) {
    struct process *proc = generateProcess();
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
      // Remove next process from ready queue
      struct process *cur = listPop();
    pthread_mutex_unlock(&syncReadyQueue);

    short oldState = cur->iState;
    int oldBurstTime = cur->iBurstTime;
    simulateRoundRobinProcess(cur, &start, &end);

    int response = 0;
    if (oldState == NEW) {
      // Calculate response time if the process was new
      response = getDifferenceInMilliSeconds(cur->oTimeCreated, start);
    }

    int turnaround = 0;
    if (cur->iState == FINISHED) {
      // Calculate turnaround time if process is finished
      turnaround = getDifferenceInMilliSeconds(cur->oTimeCreated, end);
    }

    // Outputs and add to total response and turnaround
    pthread_mutex_lock(&syncConsumer);
      printf("Consumer Id = %d, Process Id = %d, Previous Burst Time = %d, New Burst Time = %d",
        consumerID, cur->iProcessId, oldBurstTime, cur->iBurstTime);

      if (oldState == NEW)
        printf(", Response Time = %d", response);

      if (cur->iState == FINISHED)
        printf(", Turn Around Time = %d", turnaround);

      printf("\n");
      totResponse += response;
      totTurnaround += turnaround;
    pthread_mutex_unlock(&syncConsumer);

    if (cur->iState == FINISHED) {
      // Process finished - free it, post to producer
      free(cur);
      sem_post(&canProduce);

    } else {
      // Process not finished - re-add to queue and post to consumers
      pthread_mutex_lock(&syncReadyQueue); // modifying global vars - critical section
        listInsert(cur);
      pthread_mutex_unlock(&syncReadyQueue);
      sem_post(&canConsume);
    }
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
