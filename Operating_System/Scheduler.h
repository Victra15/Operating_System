#pragma once

#define READYQUEUE_SIZE 3
#define TIME_FOR_ONE_PROCESS 5

#include <iostream>
#include <queue>
#include "PCB.h"

using namespace std;

typedef struct queueheader
{
	PCB* head;
	PCB* tail;
}QueueHeader;

class Scheduler
{
private:
	PCB* runningPCB;
	QueueHeader readyQueue;
	QueueHeader deviceQueue;
	QueueHeader jobQueue;
public:
	Scheduler(QueueHeader _jobQueue);
	void start();
	void IORequest();
	void printProcess();
};

