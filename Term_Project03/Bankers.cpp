#include "Bankers.h"

Bankers::Bankers()
{
	Process* process;
	int* maxResource;
	int* allocatedResource;

	maxResource = new int[RESOUCE_TYPE_CNT] {6, 0, 1, 2};
	allocatedResource = new int[RESOUCE_TYPE_CNT] {4, 0, 0, 1};
	process = new Process(RESOUCE_TYPE_CNT, maxResource, allocatedResource);
	processes.push_back(process);

	maxResource = new int[RESOUCE_TYPE_CNT] {1, 7, 5, 0};
	allocatedResource = new int[RESOUCE_TYPE_CNT] {1, 1, 0, 0};
	process = new Process(RESOUCE_TYPE_CNT, maxResource, allocatedResource);
	processes.push_back(process);

	maxResource = new int[RESOUCE_TYPE_CNT] {2, 3, 5, 6};
	allocatedResource = new int[RESOUCE_TYPE_CNT] {1, 2, 5, 4};
	process = new Process(RESOUCE_TYPE_CNT, maxResource, allocatedResource);
	processes.push_back(process);

	maxResource = new int[RESOUCE_TYPE_CNT] {1, 6, 5, 3};
	allocatedResource = new int[RESOUCE_TYPE_CNT] {0, 6, 3, 3};
	process = new Process(RESOUCE_TYPE_CNT, maxResource, allocatedResource);
	processes.push_back(process);

	maxResource = new int[RESOUCE_TYPE_CNT] {1, 6, 5, 6};
	allocatedResource = new int[RESOUCE_TYPE_CNT] {0, 2, 1, 2};
	process = new Process(RESOUCE_TYPE_CNT, maxResource, allocatedResource);
	processes.push_back(process);

	availableResources = new int[RESOUCE_TYPE_CNT] {3, 2, 1, 1};
}

Bankers::~Bankers()
{
	for (int loop = 0; loop < processes.size(); loop++)
		delete processes[loop];
}

void Bankers::find_safe_sequence()
{
	int* maxResource;
	int* allocatedResource;

	for (int loop1 = 0; loop1 < processes.size(); loop1++)
	{
		maxResource = processes[loop1]->getMaxResouce();
		allocatedResource = processes[loop1]->getAllocatedResource();
		
		for (int loop2 = 0; loop2 < RESOUCE_TYPE_CNT; loop2++)
		{
			if (maxResource[loop2] - allocatedResource[loop2] > availableResources[loop2])
				break;
		}
		

	}
}

void Bankers::print()
{
	int* maxResource;
	int* allocatedResource;
	
	std::cout << "   " << "Max" << "\t" << "\t" << "Allocation" << "\t" << "Available" << endl;
	std::cout << "   " << "A B C D" << "\t" << "A B C D" << "\t" << "\t" << "A B C D" << endl;

	for (int loop1 = 0; loop1 < processes.size(); loop1++)
	{
		maxResource = processes[loop1]->getMaxResouce();
		allocatedResource = processes[loop1]->getAllocatedResource();

		std::cout << "P" << loop1 << ":";
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
}