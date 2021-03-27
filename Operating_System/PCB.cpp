#include "PCB.h"


PCB::PCB(string _Pname, int _PID, int _total_job)
{
	Pname = _Pname;
	Pstate = NEW;
	PID = _PID;
	current_job = 0;

	if (_total_job > 0)
		total_job = _total_job;
	else
		total_job = 0;
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