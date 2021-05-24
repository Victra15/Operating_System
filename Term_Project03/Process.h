#pragma once

class Process
{
private:
	int resourceTypeCnt;
	int* maxResource;
	int* allocatedResource;
public:
	Process(int _resourceTypeCnt, int* _maxResource, int* _allocatedResource);
	~Process();
	void resourceAllocate(int* allocate);
	int* getMaxResouce();
	int* getAllocatedResource();
};

