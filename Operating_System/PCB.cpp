#include "PCB.h"


PCB::PCB(string _Pname, int _PID, int _total_job, bool _IORequire, int _IORequireTime)
{
	Pname = _Pname;
	Pstate = NEW;
	PID = _PID;
	current_job = 0;

	if (_total_job > 0)
		total_job = _total_job;
	else
		total_job = 0;
	IORequire = _IORequire;

	if (IORequireTime > 0 && IORequireTime < total_job)
		IORequireTime = _IORequireTime;
	else
		IORequireTime = 0;
}



void PCB::process_run()
{
	if (current_job < total_job)
		current_job++;
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



int PCB::getCurrent_job()
{
	return current_job;
}



int PCB::getTotal_job()
{
	return total_job;
}



bool PCB::getIORequire()
{
	return IORequire;
}



int PCB::getIORequireTime()
{
	return IORequireTime;
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



void PCB::setCurrent_job(int _current_job)
{
	current_job = _current_job;
}



void PCB::setTotal_job(int _total_job)
{
	total_job = _total_job;
}



void PCB::setIORequire(bool _IORequire)
{
	IORequire = _IORequire;
}



void PCB::setIORequireTime(int _IORequireTime)
{
	IORequireTime = _IORequireTime;
}