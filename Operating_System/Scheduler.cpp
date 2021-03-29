#include "Scheduler.h"
#include <Windows.h>
Scheduler::Scheduler(queue<PCB*> _jobQueue)
{
	jobQueue = _jobQueue;
	runningPCB = NULL;
	readyQueueCounter = 0;
	deviceQueueCounter = 0;
}


void Scheduler::start()
{
	while(!jobQueue.empty())
	{
		IOCompletion();
		admitted();
		scheduler_dispatch();
		IOCompletion();
		admitted();

		cout << "#" << runningPCB->getPname() << " Process running..." << endl;
		printProcess();
		cout << endl;
		

		for (int count = 0; count < TIME_FOR_ONE_PROCESS; count++)
		{
			runningPCB->process_run();
			cout << "\r";
			cout << "Process " << "(" << runningPCB->getCurrent_job() << "/" << runningPCB->getTotal_job() << ")" << " completed. ";
			IOProcess_run();
			//Sleep(100);
			if (runningPCB->getIORequire() && (runningPCB->getIORequireTime() == runningPCB->getCurrent_job()))
			{
				cout << endl << endl;
				cout << "#" << runningPCB->getPname() << " I/O Event" << endl;
				IOWait();
				printProcess();
				break;
			}
			if (runningPCB->getCurrent_job() == runningPCB->getTotal_job())
			{
				cout << endl << endl;
				cout << "#" << runningPCB->getPname() << " Terminated." << endl;
				runningPCB->setPstate(TERMINATED);
				exit();
				delete runningPCB;
				runningPCB = NULL;
				printProcess();
				break;
			}
		}
		
		if(readyQueue.tail != NULL)
			interrupt();

		cout << endl << endl;
	}
}



void Scheduler::IOProcess_run()
{
	if (deviceQueue.head != NULL)
	{
		PCB* curr = deviceQueue.head;
		while (curr != NULL)
		{
			if (!curr->getIOComplete())
			{
				curr->IOProcess();
				cout << curr->getPname() << " I/O Process " << "(" << curr->getCurrent_IO_job() << "/" << curr->getTotal_IO_job() << ") completed.";
				if (curr->getIOComplete())
				{
					cout << endl << endl;
					cout << "#" << curr->getPname() << " I/O finished" << endl;
					printProcess();
					cout << endl;
				}
				break;
			}
			else
			{
				curr = curr->getPointer();
			}
		}
	}
}



void Scheduler::admitted()
{
	queue<PCB*> new_jobQueue = jobQueue;
	PCB* curr;

	while(!new_jobQueue.empty() && readyQueueCounter < READYQUEUE_SIZE)
	{
		curr = new_jobQueue.front();
		new_jobQueue.pop();

		if (curr->getPstate() == NEW)
		{
			if (readyQueue.tail == NULL)
			{
				readyQueue.head = curr;
				readyQueue.tail = curr;
			}
			else
			{
				readyQueue.tail->setPointer(curr);
				readyQueue.tail = curr;
			}
			curr->setPstate(READY);
			readyQueueCounter++;
		}
	}
}



void Scheduler::scheduler_dispatch()
{
	if (runningPCB == NULL && readyQueue.head != NULL)
	{
		runningPCB = readyQueue.head;
		
		if (readyQueue.head == readyQueue.tail)
			readyQueue.tail = NULL;

		readyQueue.head = readyQueue.head->getPointer();
		runningPCB->setPointer(NULL);
		runningPCB->setPstate(RUNNING);
		readyQueueCounter--;
	}
}



void Scheduler::interrupt()
{
	if (runningPCB != NULL)
	{
		if (readyQueue.tail != NULL)
		{
			readyQueue.tail->setPointer(runningPCB);
			readyQueue.tail = runningPCB;
		}
		else
		{
			readyQueue.head = runningPCB;
			readyQueue.tail = runningPCB;
		}
		runningPCB->setPstate(READY);
		readyQueueCounter++;
		runningPCB = NULL;
	}
}



void Scheduler::IOWait()
{
	if (runningPCB != NULL)
	{
		if (deviceQueue.tail != NULL)
		{
			deviceQueue.tail->setPointer(runningPCB);
			deviceQueue.tail = runningPCB;
		}
		else
		{
			deviceQueue.head = runningPCB;
			deviceQueue.tail = runningPCB;
		}
		runningPCB->setPstate(WAITING);
		runningPCB->setIOComplete(false);
		runningPCB = NULL;
	}
}


void Scheduler::IOCompletion()
{
	if (deviceQueue.head != NULL && readyQueueCounter < READYQUEUE_SIZE && deviceQueue.head->getIOComplete())
	{
		if (readyQueue.tail != NULL)
		{
			readyQueue.tail->setPointer(deviceQueue.head);
		}
		else
		{
			readyQueue.head = deviceQueue.head;
		}
		readyQueue.tail = deviceQueue.head;
		readyQueue.tail->setPstate(READY);
		
		if (deviceQueue.head == deviceQueue.tail)
			deviceQueue.tail = NULL;
		
		deviceQueue.head = deviceQueue.head->getPointer();
		readyQueue.tail->setPointer(NULL);
	}
}



void Scheduler::exit()
{
	queue<PCB*> temp_queue;

	while (!jobQueue.empty())
	{
		if (jobQueue.front() != runningPCB)
		{
			temp_queue.push(jobQueue.front());
		}
		jobQueue.pop();
	}
	jobQueue = temp_queue;
}



void Scheduler::printProcess()
{
	queue<PCB*> copy_job_queue = jobQueue;
	cout << "Running : ";
	if(runningPCB != NULL)
		cout << runningPCB->getPname();
	cout << endl;

	cout << "Ready : ";
	for (PCB* curr = readyQueue.head; curr != NULL; curr = curr->getPointer())
	{
		if (curr->getPointer() == NULL)
			cout << curr->getPname();
		else
			cout << curr->getPname() << ", ";
	}
	cout << endl;

	cout << "Wait : ";
	for (PCB* curr = deviceQueue.head; curr != NULL; curr = curr->getPointer())
	{
		if (curr->getPointer() == NULL)
			cout << curr->getPname();
		else
			cout << curr->getPname() << ", ";
	}
	cout << endl;

	cout << "Job Queue : ";
	while (!copy_job_queue.empty())
	{
		if (copy_job_queue.front()->getPstate() != TERMINATED)
		{
			cout << copy_job_queue.front()->getPname();
			copy_job_queue.pop();
			if (!copy_job_queue.empty())
				cout << ", ";
		}
	}
}	