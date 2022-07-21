#include <iostream>
#include <random>
#include <algorithm>
#include <cassert>

template <size_t arrayLength>
int binarySearch(int(&arr)[arrayLength], int targetValue)
{
	int min = 0, max = arrayLength - 1;
	
	while (max >= min)
	{
		int guess = (max + min) / 2;
		int guessValue = arr[guess];
		if (guessValue == targetValue)
			return guess;
		else if (guessValue > targetValue)
			max = guess - 1;
		else
			min = guess + 1;
	}

	return -1;
}

int binarySearchRecursive(int arr[], int targetValue, int lowerRangeBound, int upperRangeBound)
{
	if (lowerRangeBound > upperRangeBound)
		return -1;

	int guess = (lowerRangeBound + upperRangeBound) / 2;
	int guessValue = arr[guess];

	if (guessValue == targetValue)
		return guess;

	if (guessValue > targetValue)
		return binarySearchRecursive(arr, targetValue, lowerRangeBound, guess - 1);

	return binarySearchRecursive(arr, targetValue, guess + 1, upperRangeBound);
}

template <size_t arrayLength>
int binarySearchRecursive(int(&arr)[arrayLength], int targetValue)
{
	return binarySearchRecursive(arr, targetValue, 0, arrayLength - 1);
}

const int TEST_ARRAY_LENGTH = 1000;

int main()
{
	int arr[TEST_ARRAY_LENGTH];
	int arr2[TEST_ARRAY_LENGTH];

	for (int i = 0; i < TEST_ARRAY_LENGTH; i++)
	{
		int val = rand() % 100000;
		arr[i] = val;
		arr2[i] = val;
	}

	std::sort(arr, arr + TEST_ARRAY_LENGTH);
	
	bool flag = true;

	for (int i = 0; i < 10000; i++)
	{
		int randind = rand() % TEST_ARRAY_LENGTH;
		int target = arr2[randind];

		int expectedInd1 = binarySearch(arr, target);
		if (target != arr[expectedInd1]) flag = false;

		int expectedInd2 = binarySearchRecursive(arr, target);
		if (target != arr[expectedInd1]) flag = false;
	}

	assert(flag);
}
