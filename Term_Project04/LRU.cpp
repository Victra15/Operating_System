#pragma once
#include "LRU.h"

LRU::LRU()
{
	for (int loop = 0; loop < PAGE_FRAME_CNT; loop++)
	{
		page_frame[loop] = -1;
	}
}

void LRU::pageReplacement(string reference_string)
{
	int page_fault = 0;

	int empty_index;
	bool pageFrameIsFull = false;
	char ref;
	int ref_int;

	for (int ref_loop = 0; ref_loop < reference_string.length(); ref_loop++)
	{
		ref = reference_string.at(ref_loop);
		ref_int = ctoi(ref);
		if (findItem(page_frame, PAGE_FRAME_CNT, ref_int)) continue;
		if (findArrEmpty(page_frame, PAGE_FRAME_CNT, empty_index))
		{
			page_frame[empty_index] = ref_int;
			page_fault++;
			printString(reference_string, ref_loop);
			cout << "Page Fault: " << page_fault << endl;
			printPageFrame();
			cout << endl;
			continue;
		}

		int max_length, length;
		int replace_index = 0;
		max_length = 0;

		for (int frame_loop = 0; frame_loop < PAGE_FRAME_CNT; frame_loop++)
		{
			length = 0;
			for (int str_loop = ref_loop; str_loop >= 0; str_loop--)
			{
				if (page_frame[frame_loop] == ctoi(reference_string.at(str_loop)))
				{

					break;
				}
				length++;
			}

			if (max_length < length)
			{
				max_length = length;
				replace_index = frame_loop;
			}
		}
		page_frame[replace_index] = ref_int;
		page_fault++;
		printString(reference_string, ref_loop);
		cout << "Page Falut: " << page_fault << endl;
		printPageFrame();
		cout << endl;
	}
}