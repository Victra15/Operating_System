#pragma once
#include <iostream>
#include <iomanip>
#include <vector>
#include <queue>
#include "Process.h"

using namespace std;

#define RESOUCE_TYPE_CNT 4

class Bankers
{
private:
	int* availableResources;
	vector<Process*> processes;
public:
	Bankers();
	~Bankers();
	void find_safe_sequence();
	void ResourceAllocation(const char* processName, int* request);
	void print();
};

