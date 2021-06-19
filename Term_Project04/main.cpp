#include <iostream>
#include "LRU.h"
#include "Optimal.h"

using namespace std;

int main()
{
	Optimal Optimal_page_replace;
	LRU LRU_page_replace;

	string reference_string = "121456346373153734241451";
	
	cout << "[ Optimal ]" << endl;
	Optimal_page_replace.pageReplacement(reference_string);
	cout << "[ LRU ]" << endl;
	LRU_page_replace.pageReplacement(reference_string);

	return 0;
}