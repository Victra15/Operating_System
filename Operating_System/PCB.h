#pragma once
#include <iostream>
#include <string>

using namespace std;

enum ProcessState
{
	NEW, 
	RUNNING, 
	WAITING, 
	READY, 
	TERMINATED
};

class PCB
{
private:
	string Pname;
	ProcessState Pstate;
	PCB* Pointer;
	int PID;
	int current_job;
	int total_job;
public:
	PCB(string _Pname, int _PID, int total_job);
	void process_run();

	string getPname();
	ProcessState getPstate();
	PCB* getPointer();
	int getPID();
	int getCurrent_job();
	int getTotal_job();

	void setPname(string _Pname);
	void setPstate(ProcessState _Pstate);
	void setPointer(PCB* _Pointer);
	void setPID(int _PID);
	void setCurrent_job(int _current_job);
	void setTotal_job(int _total_job);
	
};

