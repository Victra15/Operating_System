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
	bool IORequire;
	int IORequireTime;
	bool IOComplete;
	int total_IO_job;
	int current_IO_job;
public:
	PCB(string _Pname, int _PID, int total_job, bool _IORequire, int _IORequireTime, int _total_IO_job);
	void process_run();
	void IOProcess();

	string getPname();
	ProcessState getPstate();
	PCB* getPointer();
	int getPID();
	int getCurrent_job();
	int getTotal_job();
	bool getIORequire();
	int getIORequireTime();
	bool getIOComplete();
	int getTotal_IO_job();
	int getCurrent_IO_job();

	void setPname(string _Pname);
	void setPstate(ProcessState _Pstate);
	void setPointer(PCB* _Pointer);
	void setPID(int _PID);
	void setCurrent_job(int _current_job);
	void setTotal_job(int _total_job);
	void setIORequire(bool _IORequire);
	void setIORequireTime(int _IORequireTime);
	void setIOComplete(bool IOComplete);
};

