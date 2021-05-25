#include <iostream>
#include "Bankers.h"
#include "Process.h"

using namespace std;

int main()
{
	Bankers* banker = new Bankers();

	banker->print();
	banker->find_safe_sequence();

	delete banker;

	banker = new Bankers();

	int* request = new int[RESOUCE_TYPE_CNT] { 1,2,0,0 };

	banker->ResourceAllocation("P4", request);
	banker->print();
	banker->find_safe_sequence();

	delete banker;
	delete[] request;
	return 0;

}
