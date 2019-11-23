#pragma once
#include "heap.h"
#include <iostream>
#include <assert.h>
#include "TestP14.h"

int main()
{
	std::vector<int> arr;
	arr.push_back(47);
	arr.push_back(65);
	arr.push_back(-7);
	arr.push_back(22);
	arr.push_back(99);
	arr.push_back(108);
	arr.push_back(200);
	arr.push_back(55);
	arr.push_back(3);
	arr.push_back(-54);
	arr.push_back(62);
	assert(arr.size() == 11);
	int product = computeProduct(arr, 4, 3);
	assert(product == 138996000);
	std::cout << "really short test works\n";
	
	testP14();
}