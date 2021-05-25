#pragma once

class Process
{
private:
	const char* processName;
	int resourceTypeCnt;
	int* maxResource;
	int* allocatedResource;
public:
	Process(const char* _processName, int _resourceTypeCnt, int* _maxResource, int* _allocatedResource);
	~Process();
	void resourceAllocate(int* allocate);
	int* getMaxResouce();
	int* getAllocatedResource();
	const char* getProcessName();
};

