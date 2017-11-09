// Process scheduling - shortest job first
#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>
#include "coursework.h"

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

// Remove head of list
void listRemove(struct process **head) {
  struct process *temp = *head;
  *head = (*head)->oNext;
  free(temp);
}

sem_t sync, canProduce, canConsume;
struct process *head = NULL; // shared pointer to head of list

void *producer(void *arg) {
  for (int i=0; i < NUMBER_OF_PROCESSES; i++) {
    struct process* proc = generateProcess();
    sem_wait(&sync);

    listInsert(&head, proc);

    sem_post(&canConsume);
    sem_post(&sync);
  }

  return NULL;
}

void *consumer(void *arg) {
  struct timeval *start = malloc(sizeof(struct timeval)),
    *end = malloc(sizeof(struct timeval));

  int oldBurstTime;
  long int response, turnaround;
  int totResponse = 0, totTurnaround = 0;

  for (int i=0; i < NUMBER_OF_PROCESSES; i++) {
    sem_wait(&canConsume);
    sem_wait(&sync);

    oldBurstTime = head->iBurstTime;
    simulateSJFProcess(head, start, end);

    response = getDifferenceInMilliSeconds(head->oTimeCreated, *start);
    totResponse += response;

    turnaround = getDifferenceInMilliSeconds(*start, *end);
    totTurnaround += turnaround;

    printf("Process Id = %d, Previous Burst Time = %d, New Burst Time = %d, Response Time = %li, "
      "Turn Around Time = %li\n",
      head->iProcessId, oldBurstTime, head->iBurstTime,
      response, turnaround);

    listRemove(&head);
    sem_post(&canProduce); // new space in buffer
    sem_post(&sync); // exit critial section
  }

  printf("Average response time = %lf\nAverage turn around time = %lf\n",
    (double) totResponse /NUMBER_OF_PROCESSES, (double) totTurnaround /NUMBER_OF_PROCESSES);

  return NULL;
}

int main(int argc, char **argv) {
  // Producer semaphore starts at BUFFER_SIZE to track if full
  sem_init(&canProduce, 0, -BUFFER_SIZE);
  sem_init(&sync, 0, 1);

  pthread_t producerT, consumerT;
  pthread_create(&producerT, NULL, &producer, NULL);
  pthread_create(&consumerT, NULL, &consumer, NULL);

  pthread_join(producerT, NULL);
  pthread_join(consumerT, NULL);
  return 0;
}
