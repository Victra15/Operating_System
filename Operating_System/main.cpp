#include <iostream>
#include <windows.h>
#include "Scheduler.h"

using namespace std;

int main()
{
	for (int i = 1; i < 100; i++)
	{
		cout << "\r";
		cout << "name of " << i;
		Sleep(50);
	}
	


	return 0;
}