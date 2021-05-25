#include "Bankers.h"

Bankers::Bankers()
{
	Process* process;
	int* maxResource;
	int* allocatedResource;

	maxResource = new int[RESOUCE_TYPE_CNT] {6, 0, 1, 2};
	allocatedResource = new int[RESOUCE_TYPE_CNT] {4, 0, 0, 1};
	process = new Process("P0", RESOUCE_TYPE_CNT, maxResource, allocatedResource);
	processes.push_back(process);

	maxResource = new int[RESOUCE_TYPE_CNT] {1, 7, 5, 0};
	allocatedResource = new int[RESOUCE_TYPE_CNT] {1, 1, 0, 0};
	process = new Process("P1", RESOUCE_TYPE_CNT, maxResource, allocatedResource);
	processes.push_back(process);

	maxResource = new int[RESOUCE_TYPE_CNT] {2, 3, 5, 6};
	allocatedResource = new int[RESOUCE_TYPE_CNT] {1, 2, 5, 4};
	process = new Process("P2", RESOUCE_TYPE_CNT, maxResource, allocatedResource);
	processes.push_back(process);

	maxResource = new int[RESOUCE_TYPE_CNT] {1, 6, 5, 3};
	allocatedResource = new int[RESOUCE_TYPE_CNT] {0, 6, 3, 3};
	process = new Process("P3", RESOUCE_TYPE_CNT, maxResource, allocatedResource);
	processes.push_back(process);

	maxResource = new int[RESOUCE_TYPE_CNT] {1, 6, 5, 6};
	allocatedResource = new int[RESOUCE_TYPE_CNT] {0, 2, 1, 2};
	process = new Process("P4", RESOUCE_TYPE_CNT, maxResource, allocatedResource);
	processes.push_back(process);

	availableResources = new int[RESOUCE_TYPE_CNT] {3, 2, 1, 1};
}

Bankers::~Bankers()
{
	for (int loop = 0; loop < processes.size(); loop++)
		delete processes[loop];
}

void Bankers::ResourceAllocation(const char* processName, int* request)
{
	for (int ProcessLoop = 0; ProcessLoop < processes.size(); ProcessLoop++)
	{
		if (processes[ProcessLoop]->getProcessName() == processName)
		{
			int* allocatedResource = processes[ProcessLoop]->getAllocatedResource();
			for (int ResourceLoop = 0; ResourceLoop < RESOUCE_TYPE_CNT; ResourceLoop++)
			{
				allocatedResource[ResourceLoop] += request[ResourceLoop];
				availableResources[ResourceLoop] -= request[ResourceLoop];
			}
		}
	}
}

void Bankers::find_safe_sequence()
{
	int* maxResource;
	int* allocatedResource;
	int* needResource = new int[RESOUCE_TYPE_CNT];
	int AllocationLoop, ProcessLoop, ResourceLoop;
	int totalAllocation = processes.size();
	queue<const char*> safeSequenceQueue;

	for (AllocationLoop = 0; AllocationLoop < totalAllocation; AllocationLoop++)
	{
		for (ProcessLoop = 0; ProcessLoop < processes.size(); ProcessLoop++)
		{
			maxResource = processes[ProcessLoop]->getMaxResouce();
			allocatedResource = processes[ProcessLoop]->getAllocatedResource();

			for (ResourceLoop = 0; ResourceLoop < RESOUCE_TYPE_CNT; ResourceLoop++)
			{
				needResource[ResourceLoop] = maxResource[ResourceLoop] - allocatedResource[ResourceLoop];
				if (needResource[ResourceLoop] > availableResources[ResourceLoop])
					break;
			}
			
			if (ResourceLoop == RESOUCE_TYPE_CNT)
			{
				for (ResourceLoop = 0; ResourceLoop < RESOUCE_TYPE_CNT; ResourceLoop++)
				{
					availableResources[ResourceLoop] += allocatedResource[ResourceLoop];
				}
				safeSequenceQueue.push(processes[ProcessLoop]->getProcessName());
				processes.erase(processes.begin() + ProcessLoop);
				print();
			}
		}
		if ((ProcessLoop == processes.size()) && (ResourceLoop != RESOUCE_TYPE_CNT))
		{
			cout << "This system is unsafe." << endl;
			break;
		}
	}

	if (AllocationLoop == totalAllocation)
	{
		cout << "This system is safe." << endl;
		cout << "Safe Sequence : ";
		cout << safeSequenceQueue.front();
		safeSequenceQueue.pop();
		while (!safeSequenceQueue.empty())
		{
			cout << " -> " << safeSequenceQueue.front();
			safeSequenceQueue.pop();	
		}
		cout << endl << endl;
	}
	
}

void Bankers::print()
{
	int* maxResource;
	int* allocatedResource;
	
	std::cout << "   " << "Max" << "\t" << "\t" << "Allocation" << "\t" << "Available" << endl;
	std::cout << "   " << "A B C D" << "\t" << "A B C D" << "\t" << "\t" << "A B C D" << endl;

	if (processes.size() == 0)
	{
		std::cout << "   " << "\t" << "\t" << "\t" << "\t";
		for (int loop2 = 0; loop2 < RESOUCE_TYPE_CNT; loop2++)
		{
			std::cout << availableResources[loop2] << " ";
		}
		std::cout << endl;
	}

	for (int loop1 = 0; loop1 < processes.size(); loop1++)
	{
		maxResource = processes[loop1]->getMaxResouce();
		allocatedResource = processes[loop1]->getAllocatedResource();

		std::cout << processes[loop1]->getProcessName() << ":";
		for (int loop2 = 0; loop2 < RESOUCE_TYPE_CNT; loop2++)
		{
				std::cout << maxResource[loop2] << " ";
		}
		std::cout << "\t";
		for (int loop2 = 0; loop2 < RESOUCE_TYPE_CNT; loop2++)
		{
				std::cout << allocatedResource[loop2] << " ";
		}
		std::cout << "\t";
		if (loop1 == 0)
		{
			for (int loop2 = 0; loop2 < RESOUCE_TYPE_CNT; loop2++)
			{
					std::cout << availableResources[loop2] << " ";
			}
		}
		std::cout << endl;
	}
	std::cout << endl;
}