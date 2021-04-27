#include <iostream>
#include "Scheduler.h"

using namespace std;

queue<PCB*> make_job_queue();

int main()
{
	queue<PCB*> jobQueue = make_job_queue();
	Scheduler scheduler(jobQueue);
	scheduler.start();

	return 0;
}

queue<PCB*> make_job_queue()
{
	queue<PCB*> jobQueue;
	PCB* PCB_ptr;

	PCB_ptr = new PCB("PCB001", 1, 100, true, 47, 20);
	jobQueue.push(PCB_ptr);

	PCB_ptr = new PCB("PCB002", 2, 64, false, 0, 0);
	jobQueue.push(PCB_ptr);

	PCB_ptr = new PCB("PCB003", 3, 30, false, 0, 0);
	jobQueue.push(PCB_ptr);

	PCB_ptr = new PCB("PCB004", 4, 40, false, 0, 0);
	jobQueue.push(PCB_ptr);

	PCB_ptr = new PCB("PCB005", 5, 90, true, 30, 20);
	jobQueue.push(PCB_ptr);

	PCB_ptr = new PCB("PCB006", 6, 70, false, 0, 0);
	jobQueue.push(PCB_ptr);

	PCB_ptr = new PCB("PCB007", 7, 55, false, 0, 0);
	jobQueue.push(PCB_ptr);

	return jobQueue;
}