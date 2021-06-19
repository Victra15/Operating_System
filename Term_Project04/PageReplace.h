#pragma once
#include <iostream>
#include <string>

using namespace std;

#define PAGE_FRAME_CNT 3

class PageReplace
{
protected:
	int page_frame[PAGE_FRAME_CNT];
public:
	PageReplace();
	void virtual pageReplacement(string reference_string) = 0;
	void printPageFrame();
	void initializePageFrame();
	int ctoi(char num);
	bool findItem(int arr[], int arr_size, int item);
	bool findArrEmpty(int arr[], int arr_size, int& index);
	void printString(string str, int index);
};
