#pragma once
#include "PageReplace.h"

PageReplace::PageReplace()
{
	for (int loop = 0; loop < PAGE_FRAME_CNT; loop++)
	{
		page_frame[loop] = -1;
	}
}

int PageReplace::ctoi(char num)
{
	switch (num)
	{
	case '0':
		return 0;
	case '1':
		return 1;
	case '2':
		return 2;
	case '3':
		return 3;
	case '4':
		return 4;
	case '5':
		return 5;
	case '6':
		return 6;
	case '7':
		return 7;
	case '8':
		return 8;
	case '9':
		return 9;
	default:
		return -1;
	}
}

bool PageReplace::findItem(int arr[], int arr_size, int item)
{
	for (int loop = 0; loop < arr_size; loop++)
	{
		if (arr[loop] == item)
			return true;
	}
	return false;
}

bool PageReplace::findArrEmpty(int arr[], int arr_size, int& index)
{
	for (int loop = 0; loop < arr_size; loop++)
	{
		if (arr[loop] == -1)
		{
			index = loop;
			return true;
		}
	}
	return false;
}

void PageReplace::printString(string str, int index)
{
	for (int loop = 0; loop < str.length(); loop++)
	{
		if (loop == index)
		{
			cout << "[" << str.at(loop) << "]";
		}
		else
		{
			cout << str.at(loop);
		}
		cout << " ";
	}
	cout << endl;
}

void PageReplace::printPageFrame()
{
	cout << "Page Frame: ";
	for (int loop = 0; loop < PAGE_FRAME_CNT; loop++)
	{
		if (page_frame[loop] != -1)
		{
			cout << page_frame[loop] << " ";
		}
	}
	cout << endl;
}

void PageReplace::initializePageFrame()
{
	for (int loop = 0; loop < PAGE_FRAME_CNT; loop++)
	{
		page_frame[loop] = -1;
	}
}