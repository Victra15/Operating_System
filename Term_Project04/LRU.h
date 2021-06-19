#pragma once
#include <iostream>
#include <string>
#include "PageReplace.h"

using namespace std;


class LRU : PageReplace
{
private:
public:
	LRU();
	void virtual pageReplacement(string reference_string);
};

