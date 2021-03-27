#include "Scheduler.h"
Scheduler::Scheduler(QueueHeader _jobQueue)
{
	jobQueue = _jobQueue;
}


void Scheduler::start()
{
	PCB* curr = jobQueue.head;

	int readyQueueCounter = 0;
	while (readyQueueCounter < READYQUEUE_SIZE)
	{
		if (curr->getPstate() == NEW)
		{
			readyQueue.head = curr;
			curr->setPstate(READY);
			readyQueueCounter++;
		}
		curr = curr->getPointer();
	}
		
		
}


void Scheduler::IORequest()
{

}


void Scheduler::printProcess()
{

}