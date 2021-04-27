#include <iostream>
#include "Scheduler.h"

using namespace std;

void setProcess(vector<PCB*>& processVector);

int main()
{
	vector<PCB*> processVector;
	Scheduler* scheduler;

	setProcess(processVector);
	scheduler = new Scheduler(processVector);
	cout << "First Come First Served(FCFS)" << endl << endl;
	scheduler->First_Come_First_Served_start();
	processVector.clear();
	delete scheduler;
	
	setProcess(processVector);
	scheduler = new Scheduler(processVector);
	cout << "Preemtive SJF" << endl << endl;
	scheduler->Preemtive_Shortest_Job_First_start();
	processVector.clear();
	delete scheduler;

	setProcess(processVector);
	scheduler = new Scheduler(processVector);
	cout << "Round Robin(RR)" << endl << endl;
	scheduler->Round_Robin_start(3);
	processVector.clear();
	delete scheduler;

	return 0;
}

void setProcess(vector<PCB*>& processVector)
{
	PCB* PCB_ptr;

	PCB_ptr = new PCB("PCB001", 0, 0, 10, false, 0, 0);
	processVector.push_back(PCB_ptr);

	PCB_ptr = new PCB("PCB002", 1, 3, 12, false, 0, 0);
	processVector.push_back(PCB_ptr);

	PCB_ptr = new PCB("PCB003", 2, 7, 4, false, 0, 0);
	processVector.push_back(PCB_ptr);

	PCB_ptr = new PCB("PCB004", 3, 10, 6, false, 0, 0);
	processVector.push_back(PCB_ptr);

	PCB_ptr = new PCB("PCB005", 4, 14, 8, false, 0, 0);
	processVector.push_back(PCB_ptr);

	PCB_ptr = new PCB("PCB006", 5, 15, 7, false, 0, 0);
	processVector.push_back(PCB_ptr);
}