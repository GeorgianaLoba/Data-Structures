#pragma once
#include "node.h"
#include "pch.h"
#include <queue>
const int null_tcomp = -999999999;

typedef int TComp;

typedef TComp TElem;

typedef bool(*Relation)(TComp, TComp);

class SortedBagIterator;

class SortedBag {
	friend class SortedBagIterator;

private:

	/*representation of SortedBag*/
	Node *tree;
	int root;
	int firstEmpty;
	int lenght;
	Relation rel;
	int capacity;

	void resetFirstEmpty();
	//TODO: void resize();
	TComp getMinimum(int startingRoot);
	TComp getMaximum(int startingRoot);
	int removeRecursively(int node, TComp e, bool &removed);
	void resize();

public:

	//constructor

	SortedBag(Relation r);



	//adds an element to the sorted bag

	void add(TComp e);



	//removes one occurrence of an element from a sorted bag

	//returns true if an element was removed, false otherwise (if e was not part of the sorted bag)

	bool remove(TComp e);



	//checks if an element appearch is the sorted bag

	bool search(TComp e) const;



	//returns the number of occurrences for an element in the sorted bag

	int nrOccurrences(TComp e) const;



	//returns the number of elements from the sorted bag

	int size() const;



	//returns an iterator for this sorted bag

	SortedBagIterator iterator() const;



	//checks if the sorted bag is empty

	bool isEmpty() const;


	void empty();


	//destructor

	~SortedBag();

};

