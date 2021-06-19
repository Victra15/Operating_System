#pragma once
#include <iostream>
#include <string>
#include "PageReplace.h"

using namespace std;

class Optimal : PageReplace
{
private:
public:
	Optimal();
	void virtual pageReplacement(string reference_string);
};

