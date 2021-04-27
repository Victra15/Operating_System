#include "PCB.h"


PCB::PCB(string _Pname, int _PID, int _arrival_time, int _burst_time, bool _IORequire, int _IORequireTime, int _IO_burst_time)
{
	Pname = _Pname;
	Pstate = NEW;
	PID = _PID;
	arrival_time = _arrival_time;
	current_burst_time = 0;

	if (_burst_time > 0)
		burst_time = _burst_time;
	else
		burst_time = 0;

	IORequire = _IORequire;

	if (_IORequireTime > 0 && _IORequireTime < burst_time)
		IORequireTime = _IORequireTime;
	else
		IORequireTime = 0;

	IO_burst_time = _IO_burst_time;
	current_IO_burst_time = 0;
	IOComplete = true;
}



void PCB::process_run()
{
	if(Pstate == RUNNING)
		if (current_burst_time < burst_time)
			current_burst_time++;
}



void PCB::IOProcess()
{
	if (IOComplete == false)
	{
		current_IO_burst_time++;
		if (IO_burst_time == current_IO_burst_time)
		{
			IOComplete = true;
		}
	}
}



string PCB::getPname()
{
	return Pname;
}



ProcessState PCB::getPstate()
{
	return Pstate;
}



PCB* PCB::getPointer()
{
	return Pointer;
}



int PCB::getPID()
{
	return PID;
}



int PCB::getCurrent_burst_time()
{
	return current_burst_time;
}



int PCB::getBurst_time()
{
	return burst_time;
}



bool PCB::getIORequire()
{
	return IORequire;
}



int PCB::getIORequireTime()
{
	return IORequireTime;
}



bool PCB::getIOComplete()
{
	return IOComplete;
}



int PCB::getIO_burst_time()
{
	return IO_burst_time;
}



int PCB::getCurrent_IO_burst_time()
{
	return current_IO_burst_time;
}


int PCB::getArrival_time()
{
	return arrival_time;
}



void PCB::setPname(string _Pname)
{
	Pname = _Pname;
}



void PCB::setPstate(ProcessState _Pstate)
{
	Pstate = _Pstate;
}



void PCB::setPointer(PCB* _Pointer)
{
	Pointer = _Pointer;
}



void PCB::setPID(int _PID)
{
	PID = _PID;
}



void PCB::setCurrent_burst_time(int _current_burst_time)
{
	current_burst_time = _current_burst_time;
}



void PCB::setBurst_time(int _burst_time)
{
	burst_time = _burst_time;
}



void PCB::setIORequire(bool _IORequire)
{
	IORequire = _IORequire;
}



void PCB::setIORequireTime(int _IORequireTime)
{
	IORequireTime = _IORequireTime;
}



void PCB::setIOComplete(bool _IOComplete)
{
	IOComplete = _IOComplete;
}