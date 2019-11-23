#pragma once
#include "Node.h"
#include "SortedBagIterator.h"


typedef int TComp;

typedef TComp TElem;

typedef bool(*Relation)(TComp, TComp);

class SortedBagIterator;

class SortedBag {

private:

	/*representation of SortedBag*/
	Node *head;
	Relation rel;
	friend class SortedBagIterator;
	
public:

	//constructor
	SortedBag(Relation r);

	//adds an element to the sorted bag
	void add(TComp e);

	//removes one occurrence of an element from a sorted bag
	//returns true if an element was removed, false otherwise (if e was not part of the sorted bag)
	bool remove(TComp e);

	//checks if an element appears is the sorted bag
	bool search(TComp e) const;

	//returns the number of occurrences for an element in the sorted bag
	int nrOccurrences(TComp e) const;

	//returns the number of elements from the sorted bag
	int size() const;

	//returns an iterator for this sorted bag
	SortedBagIterator iterator() const;

	//checks if the sorted bag is empty
	bool isEmpty() const;

	//destructor
	~SortedBag();
};