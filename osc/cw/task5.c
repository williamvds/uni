// Blocking RR with bounded buffer and multiple consumers

// Necessary for usleep
#define _DEFAULT_SOURCE
#define _BSD_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>
#include <pthread.h>
#include "coursework.h"

#define MANAGER_DELAY 20 // 20ms between each manager run

// Shared pointers to head and tail of ready queue
struct process *readyHead = NULL, *readyTail = NULL;

// Generic list insert - inserts at tail
void listInsert(struct process **head, struct process **tail, struct process *proc) {
  if (!*head) {
    *head = proc;
    *tail = proc;
    return;
  }

  (*tail)->oNext = proc;
  *tail = proc;
}

// Generic list remove - pop item from head
struct process * listPop(struct process **head) {
  struct process *temp = *head;
  *head = (*head)->oNext;
  temp->oNext = NULL;

  return temp;
}

// Structure containing information necessary to manage an individual event queue
struct eventQueue {
  struct process *head;
  struct process *tail;
  pthread_mutex_t mutex;
};

// Hold information for all event queues so consumers and manager can add/pop from them
struct eventQueue * queues[NUMBER_OF_EVENT_TYPES];

sem_t canProduce, // Track number of free spaces in ready queue
  canConsume; // Track number of processes in ready queue

// Enforce mutual exclusion when...
pthread_mutex_t syncReadyQueue, // manipulating ready queue
  syncConsumer; // writing to stdout and manipulating totals for response and turnaround times

// Track number of processes left to complete so consumers know when to exit
int processesToRun = NUMBER_OF_PROCESSES;

void * eventManager(void *arg) {
  while (1) {
    // Check each event queue
    for (int i = 0; i < NUMBER_OF_EVENT_TYPES; i++) {
      struct eventQueue *q = queues[i];
      if (!q) // exit if queue is NULL - this indicates the program is finished
        return NULL;
      else if (!q->head) // skip if queue is empty
        continue;

      // Remove first from event queue
      pthread_mutex_lock(&q->mutex);
        struct process *proc = listPop(&q->head);
      pthread_mutex_unlock(&q->mutex);

      printf("Process %d in event queue %d unblocked\n", proc->iProcessId, proc->iEventType);
      proc->iEventType = -1;


      // Add it to the ready queue
      pthread_mutex_lock(&syncReadyQueue);
        listInsert(&readyHead, &readyTail, proc);
      pthread_mutex_unlock(&syncReadyQueue);
      sem_post(&canConsume);
    }

    usleep(MANAGER_DELAY *1000); // Enforce delay between loops
  }
  return NULL;
}

void *producer(void *arg) {
  for (int i=0; i < NUMBER_OF_PROCESSES; i++) {
    struct process *proc = generateProcess();
    sem_wait(&canProduce);

    // Insert new process in ready queue
    pthread_mutex_lock(&syncReadyQueue);
      listInsert(&readyHead, &readyTail, proc);
    pthread_mutex_unlock(&syncReadyQueue);
    sem_post(&canConsume);
  }

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
      // All processes completed = wake up next consumer and terminate
      if (!processesToRun) {
        pthread_mutex_unlock(&syncReadyQueue);
        sem_post(&canConsume);
        return NULL;
      }
      // Remove next process from ready queue
      struct process *cur = listPop(&readyHead);
    pthread_mutex_unlock(&syncReadyQueue);

    short oldState = cur->iState;
    int oldBurstTime = cur->iBurstTime;
    simulateBlockingRoundRobinProcess(cur, &start, &end);

    if (cur->iState == BLOCKED) {
      // process blocked - add to respective event queue
      struct eventQueue * q = queues[cur->iEventType];
      printf("Process %d blocked on event type %d\n", cur->iProcessId, cur->iEventType);

      pthread_mutex_lock(&q->mutex);
        listInsert(&q->head, &q->tail, cur);
      pthread_mutex_unlock(&q->mutex);
      continue;
    }

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

      if (cur->iState == FINISHED) {
        printf(", Turn Around Time = %d", turnaround);
      }

      printf("\n");
      totResponse += response;
      totTurnaround += turnaround;
    pthread_mutex_unlock(&syncConsumer);

    if (cur->iState == FINISHED) {
      // Process finished - free it, decrement counter, post to producer
      free(cur);

      pthread_mutex_lock(&syncReadyQueue);
        processesToRun--;
        // Wake up other consumers if they need to exit
        if (!processesToRun)
          sem_post(&canConsume);
      pthread_mutex_unlock(&syncReadyQueue);

      sem_post(&canProduce);

    } else {
      // Process not finished - re-add to queue and post to consumers
      pthread_mutex_lock(&syncReadyQueue);
        listInsert(&readyHead, &readyTail, cur);
      pthread_mutex_unlock(&syncReadyQueue);
      sem_post(&canConsume);
    }
  }

  return NULL;
}

int main(int argc, char **argv) {
  // Producer semaphore starts at BUFFER_SIZE to track empty spaces in ready queue
  sem_init(&canProduce, 0, BUFFER_SIZE);

  pthread_t eventManagerT, producerT, consumerT[NUMBER_OF_CONSUMERS];

  // Create event queues and manager thread
  for (int i = 0; i < NUMBER_OF_EVENT_TYPES; i++) {
    queues[i] = malloc(sizeof(struct eventQueue));
  }
  pthread_create(&eventManagerT, NULL, &eventManager, NULL);

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

  // NULL first event queue to tell manager to exit, then wait for it
  queues[0] = NULL;
  pthread_join(eventManagerT, NULL);

  return 0;
}
