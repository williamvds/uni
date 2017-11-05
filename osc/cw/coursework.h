#include <sys/time.h>

// Duration of the time slice for the round robin algorithm
#define TIME_SLICE 50

// Number of processes to create
#define NUMBER_OF_PROCESSES 3

// size of the bounded buffer for task 2 onwards
#define BUFFER_SIZE 5

// number of consumers to use from task 3 onwards
#define NUMBER_OF_CONSUMERS 5

// maximum duration of the individual processes, in milli seconds. Note that the times themselves will be chosen at random in ]0,100]
#define MAX_BURST_TIME 100

// defines the number of event queues for task 5
#define NUMBER_OF_EVENT_TYPES 2

// probability (percent) that a process will block
#define BLOCKING_PROBABILITY 20

#define NEW 1
#define READY 2
#define RUNNING 3
#define BLOCKED 4
#define FINISHED 5

/*
 * Definition of the structure containing the process characteristics. These should be sufficient for the full implementation of all tasks.
 */

struct process
{
	int iProcessId;
	struct timeval oTimeCreated;
	int iBurstTime;
	struct process * oNext;
	int iState;
	int iEventType;
};

struct process * generateProcess();
long int getDifferenceInMilliSeconds(struct timeval start, struct timeval end);
void simulateSJFProcess(struct process * oTemp, struct timeval * oStartTime, struct timeval * oEndTime);
void simulateRoundRobinProcess(struct process * oTemp, struct timeval * oStartTime, struct timeval * oEndTime);
void simulateBlockingRoundRobinProcess(struct process * oTemp, struct timeval * oStartTime, struct timeval * oEndTime);
void runProcess(int iBurstTime, struct timeval * oStartTime, struct timeval * oEndTime);
int generateBurstTime(struct process * oTemp);
int generateEventType();

