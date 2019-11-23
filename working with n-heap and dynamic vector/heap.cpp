#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <exception>

//n-ary heap (heap in which any node has n descendends)
//we consider the following:
	//PARENT of node at index i (except root) is located (i-1)/n
		//(binary-heap: the parent is (i-1)/2
	//CHILDREN of node at index i are at indices (n*i)+1, (n*i)+2, ... (n*i)+n
		//(binary-heap: the children are (2*i)+1 and (2*i)+2)
	//LAST NON-LEAF node is located at index (size-2)/n, where size=size of the heap


				//don't know if size is correct
//complexity: O(n*lognsize), where n is the number of children/descendents (restore down is
//called recursively for all n children
//is relative to the height of the heap
void restoreDown(int array[], int size, int index, int n) {
	
	int* children = new int[n + 1]; //array for storing the indices of a given node
	bool running = 1;

	while (running == 1) {

		//children[i]=-1 if the node is a leaf(meaning it doesn't have any children)
		for (int i = 1; i <= n; i++) {
			//we iterate over each children of node
			if ((n*index + i) < size) {
				children[i] = (n*index + i);
			}
			else {
				children[i] = -1;
			}
		}

		int max_child_index;
		int max_child = -1;
		//we find the max child and its index;
		for (int i = 1; i <= n; i++) {
			if (children[i] != -1 && array[children[i]] > max_child) {
				max_child_index = children[i];
				max_child = array[children[i]];
			}
		}

		//if we are in the case of a leaf node, it's done, the heap is correct, so
		//we exit the while loop (and the function)
		if (max_child == -1) {
			running = 0;
			break;
		}
		//swapping to the correct position if needed
		if (array[index] < array[max_child_index]) {
				//int aux = (*array)[max_child_index];
				//(*array)[max_child_index] = (*array)[index];
				//(*array)[index] = aux;
			std::swap(array[index], array[max_child_index]);
		}

		//move to the next node
		index = max_child_index;
	}
}



//building the heap of array[0...size-1] and ary of n by calling restore down on each
//non-leaf node all the way up to the root

//complexity: O((size-1)/n * n*lognsize) = O((size-1)/n * complexity of restoreDown)
void buildHeap(int array[], int size, int n) {
	for (int i = (size - 1) / n; i >= 0; i--) {
		restoreDown(array, size, i, n);
	}
}

//function that returns the root node of the heap(which is the max) and then restores the heap
//property of the remaining nodes

//calls restoreDown once => complexity: O(n*lognsize)
int extractMax(int array[], int* size, int n) {
	int max = array[0];
	array[0] = array[*size - 1];
	*size = *size - 1;
	
	//int lenght = *size;
	//restoreDown(array, lenght, 0, n);

	restoreDown(array, *size, 0, n);
	return max;	
}

//complexity: O(k*(n*lognsize)) 
long long computeProduct(std::vector<int> array, int k, int n) {
	if (k < 0) {
		throw std::invalid_argument("the number of elems need to be positive\n");
	}
	
	if (k > array.size()) {
		return 0;
	}

	int size = array.size();

	int *new_vector = new int[size];
	int i = 0;

	for (auto elem : array) {
		new_vector[i] = elem;
		i++;
	}

	/*for (i = 0; i < size; i++) {
		new_vector.add(array[i]);
	}*/


	//buildHeap(&new_vector, i, n);
	buildHeap(new_vector, i, n);


	//if (k < size) {
	//	throw std::invalid_argument("not enough elems in the heap\n");
	//}

	long long product = 1;
	//long long currentMax;
	for (int i = 0; i < k; i++) {
		//product *= extractMax(&new_vector, &n, k);
		//std::cout << "here1";
		//currentMax = extractMax(&new_vector, &size, n);
		product *= extractMax(new_vector, &size, n);
	}
	return product;
}