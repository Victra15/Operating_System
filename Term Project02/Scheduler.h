#pragma once

#define READYQUEUE_SIZE 6
#include <iostream>
#include <vector>
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
	int readyQueueCounter;
	QueueHeader readyQueue;
	int deviceQueueCounter;
	QueueHeader deviceQueue;
	queue<PCB*> jobQueue;
	vector<PCB*> processVector;
	
public:
	Scheduler(vector<PCB*> _processVector);
	
	void First_Come_First_Served_start();
	void Preemtive_Shortest_Job_First_start();
	void Round_Robin_start(int time_quantum);

	void IOProcess_run();
	
	void SJF_admitted();
	void admitted();
	void scheduler_dispatch();
	void SJF_interrupt();
	void interrupt();
	void IOWait();
	void IOCompletion();
	void exit();

	void printProcess();
};

