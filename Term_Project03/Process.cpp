#include "Process.h"

Process::Process(const char* _processName, int _resourceTypeCnt, int* _maxResource, int* _allocatedResource)
{
	processName = _processName;
	resourceTypeCnt = _resourceTypeCnt;
	maxResource = _maxResource;
	allocatedResource = _allocatedResource;
}

Process::~Process()
{
	delete[] maxResource;
	delete[] allocatedResource;
}

void Process::resourceAllocate(int* allocate)
{
	for (int loop = 0; loop < resourceTypeCnt; loop++)
		allocatedResource[loop] += allocate[loop];
}

int* Process::getMaxResouce()
{
	return maxResource;
}

int* Process::getAllocatedResource()
{
	return allocatedResource;
}

const char* Process::getProcessName()
{
	return processName;
}