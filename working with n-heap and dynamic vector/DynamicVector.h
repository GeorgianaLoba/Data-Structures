#pragma once
//#include "DAIterator.h"
typedef int TElem;

class DynamicArray {
private:

	/*representation of Dynamic Array*/
	int length;
	int capacity;
	TElem* elements;

public:

	//constructor
	//throws exception if capacity is 0 or negative
	DynamicArray(int capacity);


	//returns the size (number of elements) from the DynamicArray
	int size() const;


	//returns the element from a given position (indexing starts from 0)

	//throws exception if pos is not a valid position

	TElem getElement(int pos) const;

	//for when the elements exceed the old capacity;
	void resize();

	//changes the element from a pozition to a different value

	//returns the old element from pozition poz

	//throws exception if pos is not a valid position

	TElem setElement(int pos, TElem newElem);


	//adds a new element to the end of the DynamicArray

	void addToEnd(TElem newElem);


	//adds a new element to a given position in a DynamicArray

	//throws exception if pos is not a valid position

	void addToPosition(int pos, TElem newElem);



	//removes an element from a given position

	//returns the removed element

	//throws exception if pos is not a valid position

	TElem remove(int pos);


	//remove all elements between two positions i and j
	//throws an exception if i and j are not valid
	void removeBetween(int i, int j);


	int& operator[](int pos);


	//destructor

	~DynamicArray();

};