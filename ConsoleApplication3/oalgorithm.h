// ConsoleApplication4.cpp : This file contains the 'main' function. Program execution begins and ends there.
//#include "safearray.h"



#pragma once
#include <cmath>
namespace oalgorithm {




	template<typename T>
	bool sorted(T* arr, int start, int end) {
		int prev = arr[start];
		for (int i = start + 1; i < end; i++)
		{
			if (arr[i] >= prev)
			{
				prev = arr[i];
			}
			else
			{
				return false;
			}
		}
		return true;
	}
	template<typename T>
	int linsearch(T* arr, int low, int high, T searchval) {


		for (int i = low; i < high; i++)
		{
			if (arr[i] == searchval) {


				return i;
			}
		}
		return -1;
	}
	template<typename T>
	int binindexsearch(T* arr, int low, int high, T searchval) {

		int index = floor((low + high) / 2);
		while (arr[index] != searchval)
		{

			if (arr[index] > searchval)
			{
				high = index - 1;

			}
			else
			{
				low = index + 1;
			}
			index = floor((low + high) / 2);
			if (low > high)
			{
				return -1;
			}
		}
		return index;


	}


	template <typename T>
	int parttion(T* arr, int low, int high)
	{
		T pivot = arr[int(floor((high + low) / 2))];
		int leftind = low - 1;
		int rightind = high + 1;

		while (true)
		{

			do
			{
				leftind++;
			} while (arr[leftind] < pivot);
			do
			{
				rightind--;
			} while (arr[rightind] > pivot);

			if (leftind >= rightind)
			{
				return rightind;
			}
			T carry = arr[leftind];
			arr[leftind] = arr[rightind];
			arr[rightind] = carry;

		}

	}


	template <typename T>
	void quicksub(T* arr, int low, int high) {

		if (low < high)
		{
			int p = parttion(arr, low, high);

			quicksub(arr, low, p);
			quicksub(arr, p + 1, high);
		}



	}



	template <typename T>
	void quicksort(T* arr, int len) {
		quicksub(arr, 0, len - 1);
	}





}

