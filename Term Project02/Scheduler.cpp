#include "Scheduler.h"
#include <Windows.h>
Scheduler::Scheduler(vector<PCB*> _processVector)
{
	processVector = _processVector;
	runningPCB = NULL;
	readyQueueCounter = 0;
	deviceQueueCounter = 0;
}

void Scheduler::First_Come_First_Served_start()
{
	int time_count = 0;
	int total_waiting_time = 0;
	vector<int> processWaitingTime(processVector.size(), 0);

	while (true)
	{
		for (vector<PCB*>::iterator iter = processVector.begin(); iter != processVector.end(); iter++)
			if ((*iter)->getArrival_time() == time_count)
			{
				jobQueue.push(*iter);
			}
		IOCompletion();
		admitted();
		scheduler_dispatch();
		IOCompletion();
		admitted();

		cout << "Current Time: " << time_count << endl;
		printProcess();

		//콘솔 정리용
		//Sleep(100);
		//cout << "\x1b[6A";
		//

		runningPCB->process_run();
		IOProcess_run();
		time_count++;
		for (PCB* curr = readyQueue.head; curr != NULL; curr = curr->getPointer())
		{
			processWaitingTime[curr->getPID()]++;
		}

		if (runningPCB->getIORequire() && (runningPCB->getIORequireTime() == runningPCB->getCurrent_burst_time()))
		{
			IOWait();
		}
		if (runningPCB->getCurrent_burst_time() == runningPCB->getBurst_time())
		{
			runningPCB->setPstate(TERMINATED);
			exit();
			delete runningPCB;
			runningPCB = NULL;
		}

		if (jobQueue.empty())
		{
			cout << "Current Time: " << time_count << endl;
			printProcess();

			cout << "waiting time" << endl;
			for (int loop = 0; loop < processWaitingTime.size(); loop++)
			{
				cout << "process" << loop + 1 << " : " << processWaitingTime[loop] << endl;
				total_waiting_time += processWaitingTime[loop];
			}
			cout << "total_waiting_time : " << total_waiting_time << endl;
			cout << "average_waiting_time : " << double(total_waiting_time) / double(processWaitingTime.size()) << endl << endl;
			
			return;
		}
	}
}

void Scheduler::Preemtive_Shortest_Job_First_start()
{
	int time_count = 0;
	int total_waiting_time = 0;
	vector<int> processWaitingTime(processVector.size(), 0);
	PCB* PCBPointer;

	while (true)
	{
		for (vector<PCB*>::iterator iter = processVector.begin(); iter != processVector.end(); iter++)
			if ((*iter)->getArrival_time() == time_count)
			{
				if (runningPCB != NULL && runningPCB->getBurst_time() - runningPCB->getCurrent_burst_time() > (*iter)->getBurst_time())
					SJF_interrupt();
				jobQueue.push(*iter);
			}
		IOCompletion();
		SJF_admitted();
		scheduler_dispatch();
		IOCompletion();
		SJF_admitted();
		
		cout << "Current Time: " << time_count << endl;
		printProcess();

		//콘솔 정리용
		//Sleep(100);
		//cout << "\x1b[6A";
		//

		runningPCB->process_run();
		IOProcess_run();
		time_count++;
		for (PCB* curr = readyQueue.head; curr != NULL; curr = curr->getPointer())
		{
			processWaitingTime[curr->getPID()]++;
		}

		if (runningPCB->getIORequire() && (runningPCB->getIORequireTime() == runningPCB->getCurrent_burst_time()))
		{
			IOWait();
		}
		if (runningPCB->getCurrent_burst_time() == runningPCB->getBurst_time())
		{
			runningPCB->setPstate(TERMINATED);
			exit();
			delete runningPCB;
			runningPCB = NULL;
		}

		if (jobQueue.empty())
		{
			cout << "Current Time: " << time_count << endl;
			printProcess();

			cout << "waiting time" << endl;
			for (int loop = 0; loop < processWaitingTime.size(); loop++)
			{
				cout << "process" << loop + 1 << " : " << processWaitingTime[loop] << endl;
				total_waiting_time += processWaitingTime[loop];
			}
			cout << "total_waiting_time : " << total_waiting_time << endl;
			cout << "average_waiting_time : " << double(total_waiting_time) / double(processWaitingTime.size()) << endl << endl;

			return;
		}
	}
}


void Scheduler::Round_Robin_start(int time_quantum)
{
	int time_count = 0;
	int total_waiting_time = 0;
	vector<int> processWaitingTime(processVector.size(), 0);

	while (true)
	{
		for (vector<PCB*>::iterator iter = processVector.begin(); iter != processVector.end(); iter++)
			if ((*iter)->getArrival_time() == time_count)
			{
				jobQueue.push(*iter);
			}

		IOCompletion();
		admitted();
		
		if (time_count % time_quantum == 0)
			interrupt();
		
		scheduler_dispatch();
		IOCompletion();
		admitted();

		cout << "Current Time: " << time_count << endl;
		printProcess();

		
		//콘솔 정리용
		//Sleep(100);
		//cout << "\x1b[6A";
		//

		runningPCB->process_run();
		IOProcess_run();
		time_count++;
		for (PCB* curr = readyQueue.head; curr != NULL; curr = curr->getPointer())
		{
			processWaitingTime[curr->getPID()]++;
		}

		if (runningPCB->getIORequire() && (runningPCB->getIORequireTime() == runningPCB->getCurrent_burst_time()))
		{
			IOWait();
		}
		if (runningPCB->getCurrent_burst_time() == runningPCB->getBurst_time())
		{
			runningPCB->setPstate(TERMINATED);
			exit();
			delete runningPCB;
			runningPCB = NULL;
		}

		
		if (jobQueue.empty())
		{
			cout << "Current Time: " << time_count << endl;
			printProcess();

			cout << "waiting time" << endl;
			for (int loop = 0; loop < processWaitingTime.size(); loop++)
			{
				cout << "process" << loop + 1 << " : " << processWaitingTime[loop] << endl;
				total_waiting_time += processWaitingTime[loop];
			}
			cout << "total_waiting_time : " << total_waiting_time << endl;
			cout << "average_waiting_time : " << double(total_waiting_time) / double(processWaitingTime.size()) << endl << endl;

			return;
		}
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
				cout << curr->getPname() << " I/O Process " << "(" << curr->getCurrent_IO_burst_time() << "/" << curr->getIO_burst_time() << ") completed.";
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


void Scheduler::SJF_admitted()
{
	queue<PCB*> new_jobQueue = jobQueue;
	PCB* curr;

	while (!new_jobQueue.empty() && readyQueueCounter < READYQUEUE_SIZE)
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
				if (readyQueue.head->getBurst_time() - readyQueue.head->getCurrent_burst_time() > curr->getBurst_time())
				{
					curr->setPointer(readyQueue.head);
					readyQueue.head = curr;
				}
				else
				{
					for (PCB* iter = readyQueue.head; iter != NULL; iter = iter->getPointer())
					{
						if (iter->getPointer() != NULL)
						{
							if (iter->getPointer()->getBurst_time() - iter->getPointer()->getCurrent_burst_time() > curr->getBurst_time())
							{
								curr->setPointer(iter->getPointer());
								iter->setPointer(curr);
								break;
							}
						}
						else
						{
							curr->setPointer(iter->getPointer());
							iter->setPointer(curr);
							readyQueue.tail = curr;
							break;
						}
					}
				}
			}
			curr->setPstate(READY);
			readyQueueCounter++;
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


void Scheduler::SJF_interrupt()
{
	if (runningPCB != NULL)
	{
		if (readyQueue.head != NULL)
		{
			runningPCB->setPointer(readyQueue.head);
			readyQueue.head = runningPCB;
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
	if (runningPCB != NULL)
	{
		cout << runningPCB->getPname();
		cout << " (" << runningPCB->getCurrent_burst_time() << "/" << runningPCB->getBurst_time() << ") completed...";
	}
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
	cout << endl << endl;
}	