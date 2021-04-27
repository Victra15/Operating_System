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
	int current_burst_time;
	int burst_time;
	bool IORequire;
	int IORequireTime;
	bool IOComplete;
	int IO_burst_time;
	int current_IO_burst_time;
	int arrival_time;
public:
	PCB(string _Pname, int _PID, int _arrival_time, int _burst_time, bool _IORequire, int _IORequireTime, int _IO_burst_time);
	void process_run();
	void IOProcess();

	string getPname();
	ProcessState getPstate();
	PCB* getPointer();
	int getPID();
	int getCurrent_burst_time();
	int getBurst_time();
	bool getIORequire();
	int getIORequireTime();
	bool getIOComplete();
	int getIO_burst_time();
	int getCurrent_IO_burst_time();
	int getArrival_time();

	void setPname(string _Pname);
	void setPstate(ProcessState _Pstate);
	void setPointer(PCB* _Pointer);
	void setPID(int _PID);
	void setCurrent_burst_time(int _current_burst_time);
	void setBurst_time(int _burst_time);
	void setIORequire(bool _IORequire);
	void setIORequireTime(int _IORequireTime);
	void setIOComplete(bool IOComplete);
};

