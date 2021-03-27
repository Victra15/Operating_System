#include "Scheduler.h"
Scheduler::Scheduler(QueueHeader _jobQueue)
{
	jobQueue = _jobQueue;
	runningPCB = NULL;
	readyQueueCounter = 0;
	deviceQueueCounter = 0;
}


void Scheduler::start()
{
	

	

	IOWait();


}



void Scheduler::admitted()
{
	for (PCB* curr = jobQueue.head; curr != NULL; curr = curr->getPointer())
	{
		if (curr->getPstate() == NEW && readyQueueCounter < READYQUEUE_SIZE)
		{
			if (readyQueueCounter == 0)
			{
				readyQueue.head = curr;
				readyQueue.tail = curr;
			}
			else
			{
				readyQueue.tail->setPointer(curr);
				readyQueue.tail = curr;
			}
		}
		else if (readyQueueCounter >= READYQUEUE_SIZE)
			break;
	}
}



void Scheduler::scheduler_dispatch()
{
	if (runningPCB == NULL)
	{
		runningPCB = readyQueue.head;

		if (readyQueue.head == readyQueue.tail)
			readyQueue.tail = NULL;

		readyQueue.head = readyQueue.head->getPointer();
	}
}



void Scheduler::interrupt()
{
	scheduler_dispatch();

}



void Scheduler::IOWait()
{
	if (runningPCB->getCurrent_job() == runningPCB->getIORequireTime() && runningPCB->getIORequire() == true)
	{
		if (deviceQueueCounter == 0)
		{
			deviceQueue.head = runningPCB;
			deviceQueue.tail = runningPCB;
		}
		else
		{
			deviceQueue.tail->setPointer(runningPCB);
			deviceQueue.tail = runningPCB;
		}
		deviceQueueCounter++;
	}
}


void Scheduler::IOCompletion()
{
	readyQueue.tail = deviceQueue.head;
	deviceQueue.head = deviceQueue.head->getPointer();
}



void Scheduler::printProcess()
{
	cout << "Running : " << runningPCB->getPname();
	for (PCB* curr = readyQueue.head; curr != NULL; curr = curr->getPointer())
		cout << "Ready : " << curr->getPname();
	for (PCB* curr = deviceQueue.head; curr != NULL; curr = curr->getPointer())
		cout << "Wait : " << curr->getPname();
	for (PCB* curr = jobQueue.head; curr != NULL; curr = curr->getPointer())
		cout << "Job Queue: " << curr->getPname();
}