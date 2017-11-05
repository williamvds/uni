#include <stdlib.h>
#include <sys/time.h>
#include "coursework.h"
#include <stdio.h>

int iPid = 0;


/*
 * Function generates asingle job and initialise the fields. Processs will have a increasing job id, reflecting the order in which they were created.
 * Note that the objects returned are allocated in dynamic memory, and that the caller is responsible for free-ing the memory when it is no longer in use.
 *
 * REMARK: note that the random generator will generate a fixed sequence of random numbers. I.e., every time the code is run, the times that are generated will be the same, although the individual
 * numbers themselves are "random". This is achieved by seeding the generator (by default), and is done to facilitate debugging if necessary.
 */
struct process * generateProcess()
{
	struct process * oTemp = (struct process *) malloc (sizeof(struct process));
	oTemp->iProcessId = iPid++;
	oTemp->iBurstTime = (rand() % MAX_BURST_TIME) + 1;
	gettimeofday(&(oTemp->oTimeCreated), NULL);
	oTemp->iState = NEW;
	oTemp->iEventType = -1;
	oTemp->oNext = NULL;
	return oTemp;
}

/*
 * Function returning the time difference in milliseconds between the two time stamps, with start being the earlier time, and end being the later time.
 */
long int getDifferenceInMilliSeconds(struct timeval start, struct timeval end)
{
	long int iSeconds = end.tv_sec - start.tv_sec;
	long int iUSeconds = end.tv_usec - start.tv_usec;
 	long int mtime = (iSeconds * 1000 + iUSeconds / 1000.0);
	return mtime;
}

/*
 * Function to call when simulating a SJF job. This function will:
 * - change the state to running
 * - run the job
 * - set the burst time of the process to 0
 * - update the state to finished
 */
void simulateSJFProcess(struct process * oTemp, struct timeval * oStartTime, struct timeval * oEndTime)
{
	oTemp->iState = RUNNING;
	runProcess(oTemp->iBurstTime, oStartTime, oEndTime);
	oTemp->iBurstTime = 0;
	oTemp->iState = FINISHED;
}

/*
 * Function to call when simulating a NON-BLOCKING round robin job. This function will:
 * - calculate the (remaining) burst time
 * - set the state to running
 * - run the job
 * - reduce the burst time of the process with the time that it ran
 * - change the state to finished if the burst time reaches 0, set it to ready if the process used its entire time slice and was taken off the CPU
 */
void simulateRoundRobinProcess(struct process * oTemp, struct timeval * oStartTime, struct timeval * oEndTime)
{
	int iBurstTime = oTemp->iBurstTime > TIME_SLICE ? TIME_SLICE : oTemp->iBurstTime;
	oTemp->iState = RUNNING;
	runProcess(iBurstTime, oStartTime, oEndTime);
	oTemp->iBurstTime -= iBurstTime;
	if(oTemp->iBurstTime == 0)
		oTemp->iState = FINISHED;
	else if (iBurstTime == TIME_SLICE)
		oTemp->iState = READY;
}

/*
 * Function to call when simulating a BLOCKING round robin job. This function will:
 * - calculate the (remaining) burst time. A random burst time in [0, min(remaining burst time, TIME_SLICE[ is returned by the generateBurstTime function if the process is expected to block (probability randomly generated)
 * - set the state to running
 * - run the job
 * - reduce the burst time of the process with the time that it ran
 * - change the state to
 *   	finished if the processe's burst time reaches 0
 *   	ready if the full time slice was used
 *   	blocked if the process did not use its full time slice and is not finished (which means that it blocked). A random event number is generated, which determines the event queue that it will end up in.
 */
void simulateBlockingRoundRobinProcess(struct process * oTemp, struct timeval * oStartTime, struct timeval * oEndTime)
{
	int iBurstTime = generateBurstTime(oTemp);
	oTemp->iState = RUNNING;
	runProcess(iBurstTime, oStartTime, oEndTime);
	oTemp->iBurstTime -= iBurstTime;
	if(oTemp->iBurstTime == 0)
		oTemp->iState = FINISHED;
	else if (iBurstTime == TIME_SLICE)
		oTemp->iState = READY;
	else if (iBurstTime < TIME_SLICE)
	{
		oTemp->iEventType = generateEventType();
		oTemp->iState = BLOCKED;
	}
}

/*
 * Simulates the job running on a CPU for a number of milli seconds
 */
void runProcess(int iBurstTime, struct timeval * oStartTime, struct timeval * oEndTime)
{
	struct timeval oCurrent;
	long int iDifference = 0;
	gettimeofday(oStartTime, NULL);
	do
	{
		gettimeofday(&oCurrent, NULL);
		iDifference = getDifferenceInMilliSeconds((*oStartTime), oCurrent);
	} while(iDifference < iBurstTime);
	gettimeofday(oEndTime, NULL);
}

/*
 * Return a burst time for the process. If the process blocks, the returned burst time will be in [0, iMaxBurstTime[, with iMaxBurstTime being equal to the minimum of the TIME_SLICE and the remaining burst time for the process.
 * If the process is non-blocking, the minimum of the TIME_SLICE and the remaining burst time for the process is returned.
 */
int generateBurstTime(struct process * oTemp)
{
	int iMaxBurstTime = oTemp->iBurstTime > TIME_SLICE ? TIME_SLICE : oTemp->iBurstTime;
	if(rand() % 100 < BLOCKING_PROBABILITY)
		return rand() % iMaxBurstTime;
	return iMaxBurstTime;
}

/*
 * Generates a number representing an event type and determining the event queue in which it should end up in
 */
int generateEventType()
{
	return rand() % NUMBER_OF_EVENT_TYPES;
}
