// Process scheduling - round-robin
#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>
#include "coursework.h"

// shared pointer to head of list and current entry
struct process *head = NULL, *tail;

// Insert process at tail
void listInsert(struct process *proc) {
  if (!head) {
    head = proc;
    tail = proc;
    return;
  }

  tail->oNext = proc;
  tail = proc;
}

// Remove item from head
struct process * listPop() {
  struct process *temp = head;
  head = head->oNext;
  temp->oNext = NULL;

  return temp;
}

sem_t canProduce, canConsume;
pthread_mutex_t sync, syncConsumer;

void *producer(void *arg) {
  for (int i=0; i < NUMBER_OF_PROCESSES; i++) {
    struct process *proc = generateProcess();
    sem_wait(&canProduce);
    pthread_mutex_lock(&sync);

    listInsert(proc);

    pthread_mutex_unlock(&sync);
    sem_post(&canConsume);
  }

  // Wake up consumers again to allow them to exit
  sem_post(&canConsume);

  return NULL;
}

int totResponse = 0, totTurnaround = 0;
void *consumer(void *arg) {
  int consumerID = *(int*) arg;
  struct timeval *start = malloc(sizeof(struct timeval)),
    *end = malloc(sizeof(struct timeval));

  while (1) {
    sem_wait(&canConsume);
    pthread_mutex_lock(&sync);

    // No processes available = wake up next consumer and terminate
    if (!head) {
      pthread_mutex_unlock(&sync);
      sem_post(&canConsume);
      return NULL;
    }

    short oldState = head->iState;
    struct process *temp = listPop(); // remove current process from queue

    pthread_mutex_unlock(&sync); // exit critial section

    int oldBurstTime = temp->iBurstTime;
    simulateRoundRobinProcess(temp, start, end);

    int response = 0;
    if (oldState == NEW) {
      // calc response time if the process was new
      response = getDifferenceInMilliSeconds(temp->oTimeCreated, *start);
    }

    int turnaround = 0;
    if (temp->iState == FINISHED) {
      // calc turnaround if process is completed
      turnaround = getDifferenceInMilliSeconds(temp->oTimeCreated, *end);
    }

    pthread_mutex_lock(&syncConsumer); // only one consumer at a time writes output and adds to totals

    printf("Consumer Id = %d, Process Id = %d, Previous Burst Time = %d, New Burst Time = %d",
      consumerID, temp->iProcessId, oldBurstTime, temp->iBurstTime);

    if (oldState == NEW)
      printf(", Response Time = %d", response);

    if (temp->iState == FINISHED)
      printf(", Turn Around Time = %d", turnaround);

    printf("\n");

    totResponse += response;
    totTurnaround += turnaround;

    pthread_mutex_unlock(&syncConsumer);

    if (temp->iState == FINISHED) {
      //
      free(temp);
      sem_post(&canProduce); // new space in buffer
    } else {
      // process has not finished - re-add to queue and increment counter
      pthread_mutex_lock(&sync); // modifying global vars - critical section
      listInsert(temp);
      pthread_mutex_unlock(&sync);
      sem_post(&canConsume);
    }
  }

  free(start);
  free(end);
  return NULL;
}

int main(int argc, char **argv) {
  // Producer semaphore starts at BUFFER_SIZE to track if full
  sem_init(&canProduce, 0, BUFFER_SIZE);

  pthread_t producerT, consumerT[NUMBER_OF_CONSUMERS];
  pthread_create(&producerT, NULL, &producer, NULL);
  for (int i = 0; i < NUMBER_OF_CONSUMERS; i++) {
    pthread_create(&consumerT[i], NULL, &consumer, (int *) &i);
  }

  pthread_join(producerT, NULL);
  for (int i = 0; i < NUMBER_OF_CONSUMERS; i++) {
    pthread_join(consumerT[i], NULL);
  }

  printf("Average response time = %lf\nAverage turn around time = %lf\n",
    (double) totResponse /NUMBER_OF_PROCESSES, (double) totTurnaround /NUMBER_OF_PROCESSES);

  return 0;
}
