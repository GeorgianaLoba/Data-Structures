#pragma once
#include "SortedBag.h"

class SortedBag;

class SortedBagIterator
{
private:
	int currentFreq;
	Node* currentNode;
	const SortedBag& bag;
	friend class SortedBag;
public:
	//Constructor receives a reference of the container.

	//after creation the iterator will refer to the first element of the container, or it will be invalid if the container is empty

	SortedBagIterator(const SortedBag& bag);

	//contains a reference of the container it iterates over

	~SortedBagIterator();
	//sets the iterator to the first element of the container

	void first();

	//moves the iterator to the next element

	//throws exception if the iterator is not valid

	void next();

	//checks if the iterator is valid

	bool valid() const;

	//returns the value of the current element from the iterator

	// throws exception if the iterator is not valid

	TElem getCurrent() const;
};