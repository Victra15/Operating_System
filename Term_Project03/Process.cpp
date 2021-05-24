#include "Process.h"

Process::Process(int _resourceTypeCnt, int* _maxResource, int* _allocatedResource)
{
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