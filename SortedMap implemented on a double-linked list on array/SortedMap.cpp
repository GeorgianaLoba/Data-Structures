#include "SortedMap.h"



SortedMap::SortedMap(Relation r) //compexity: theta(cap)
{
	this->capacity = cap;
	this->head = NULL_TVALUE;
	this->tail = NULL_TVALUE;
	this->nodes = new Node[cap];
	for (int i = 0; i < cap - 1; i++) {
		this->nodes[i].next = i + 1;
	}
	this->nodes[cap - 1].next = NULL_TVALUE;
	for (int i = 1; i < cap; i++) {
		this->nodes[i].prev = i - 1;
	}
	this->nodes[0].prev = NULL_TVALUE;
	this->rel = r;
	this->firstEmpty = 0;
	this->lenght = 0;
}


int SortedMap::allocate() //complexity theta 1
{
	int newElem = this->firstEmpty;
	if (newElem != NULL_TVALUE) {
		this->firstEmpty = this->nodes[this->firstEmpty].next;
		if (this->firstEmpty != NULL_TVALUE) {
			this->nodes[this->firstEmpty].prev = NULL_TVALUE;
		}
		this->nodes[newElem].next = NULL_TVALUE;
		this->nodes[newElem].prev = NULL_TVALUE;
	}
	return newElem;
}

void SortedMap::free(int position) { //complexity theta 1 
 	this->nodes[position].next = this->firstEmpty;
	this->nodes[position].prev = NULL_TVALUE;
	if (this->firstEmpty != NULL_TVALUE) {
		this->nodes[this->firstEmpty].prev = position;
	}
	this->firstEmpty = position;
}

void SortedMap::resize() { //complexity theta(cap)
	Node* newElems = new Node[this->capacity * 2];
	//make copy of initial elements
	for (int i = 0; i < this->capacity; i++) {
		newElems[i] = this->nodes[i];
	}
	for (int i = this->capacity; i < this->capacity * 2 - 1; i++) {
		newElems[i].next = i + 1;
	}
	newElems[2 * this->capacity-1].next = NULL_TVALUE;
	for (int i = this->capacity + 1; i < this->capacity * 2; i++) {
		newElems[i].prev = i - 1;
	}
	newElems[this->capacity].prev = NULL_TVALUE;
	this->firstEmpty = this->capacity;
	this->capacity *= 2;
	delete[] this->nodes;
	this->nodes = newElems;
}


TValue SortedMap::search(TKey c) const { //O(n)
	int current = this->head;
	while (current != NULL_TVALUE && this->nodes[current].info.first != c) {
		current = this->nodes[current].next;
	}
	if (current != NULL_TVALUE) {
		return this->nodes[current].info.second;
	}
	else {
		return NULL_TVALUE;
	}
}

int SortedMap::size() const { //theta(1)
	return this->lenght;
}

bool SortedMap::isEmpty() const { //theta(1)
	if (this->lenght == 0) {
		return true;
	}
	else {
		return false;
	}
}

TValue SortedMap::add(TKey c, TValue v) { //O(n)
	/*
	TElem new_elem;
	new_elem.first = c;
	new_elem.second = v;
	*/
	TValue old_value;
	int current = this->head;

	if (this->search(c) != NULL_TVALUE) { //the key already exists in the map
		while (current != NULL_TVALUE && this->nodes[current].info.first != c) {
			current = this->nodes[current].next;
		}
		old_value = this->nodes[current].info.second;
		this->nodes[current].info.second = v;
		return old_value;
	}
	else {
		int new_elem = this->allocate();
		if (new_elem == NULL_TVALUE) {
			this->resize();
			new_elem = this->allocate();
		}
		this->nodes[new_elem].info.first = c;
		this->nodes[new_elem].info.second = v;

		if (this->lenght == 0) { //the list is empty
			if (this->head == NULL_TVALUE && this->tail == NULL_TVALUE) {
				this->head = new_elem;
				this->tail = new_elem;
				this->lenght++;
				return NULL_TVALUE;
			}
		}
		else {
			if (this->rel(this->nodes[this->head].info.first, c) == false) { //before head or between head and tail
				this->nodes[new_elem].prev = NULL_TVALUE;
				this->nodes[new_elem].next = this->head;
				this->nodes[this->head].prev = new_elem;
				this->head = new_elem;
				this->lenght++;
				return NULL_TVALUE;
			}
			else {
				if (this->lenght == 1) {
					this->nodes[this->head].next = new_elem;
					this->nodes[new_elem].next = NULL_TVALUE;
					this->nodes[this->head].prev = this->head;
					this->tail = new_elem;
					this->lenght++;
					return NULL_TVALUE;
				}
			}
			if (this->rel(this->nodes[this->tail].info.first, c) == true) { //after tail
				this->nodes[new_elem].prev = this->tail;
				this->nodes[new_elem].next = NULL_TVALUE;
				this->nodes[this->tail].next = new_elem;
				this->lenght++;
				this->tail = new_elem;
				return NULL_TVALUE;
			}
			while (current != NULL_TVALUE && this->rel(this->nodes[this->nodes[current].next].info.first, c) != false) {
				current = this->nodes[current].next;
			}
			/*if (current == 0) {
				this->nodes[new_elem].next = this->head;
				this->nodes[this->head].prev = new_elem;
				this->head = new_elem;
				this->lenght++;
				return NULL_TVALUE;
			}
			else {*/
			/*
			int currentNode = this->head;
			int currentPos = 0;
			while (currentNode != NULL_TVALUE and currentPos < current - 1) {
				currentNode = this->nodes[currentNode].next;		
				currentPos += 1;
			}
			if (currentNode != NULL_TVALUE) {
				int nextNode = this->nodes[currentNode].next;
				this->nodes[new_elem].next = nextNode;
				this->nodes[new_elem].prev = currentNode;
				this->nodes[currentNode].next = new_elem;
				if (nextNode != NULL_TVALUE) {
					this->tail = new_elem;
				}
				else {
					this->nodes[nextNode].prev = new_elem;
				}
				this->lenght++;
				return NULL_TVALUE;
			}
			*/
			this->nodes[new_elem].prev = current;
			this->nodes[new_elem].next = this->nodes[current].next;
			this->nodes[current].next = new_elem;
			this->lenght++;
			return NULL_TVALUE;
			/*int currentNode = this->head;
			int currentPos = 0;
			while (currentNode != NULL_TVALUE and currentPos < current - 1) {
				currentNode = this->nodes[currentNode].next;
				currentPos += 1;
			}
			if (currentNode != NULL_TVALUE) {
				int nextNode = this->nodes[this->nodes[currentNode].next].next;
				this->nodes[new_elem].next = nextNode;
				this->nodes[new_elem].prev = this->nodes[currentNode].next;
				this->nodes[currentNode].next = new_elem;

			}*/
			
		}
	}
}

TValue SortedMap::remove(TKey c) { //complexity O(n)
	if (this->search(c) !=NULL_TVALUE) {
		int current = this->head;
		int previous = NULL_TVALUE;
		TValue old_value;
		while (current != NULL_TVALUE && this->nodes[current].info.first != c) {
			previous = current;
			current = this->nodes[current].next;
		}
		if (current!=NULL_TVALUE) {
			if (current == this->head && previous == NULL_TVALUE) {//we need to remove the head
				old_value = this->nodes[current].info.second;
				this->head = this->nodes[current].next;
			}
			else {
				old_value = this->nodes[current].info.second;
				this->nodes[previous].next = this->nodes[current].next;
			}
			this->nodes[current].next = this->firstEmpty;
			this->firstEmpty = current;
			this->lenght--;
			return old_value;
		}
	}
	else {
		return NULL_TVALUE;
	}
}


int SortedMap::getValueRange() const { //complexity theta(n)
	if (this->isEmpty()) {
		return -1;
	}
	int max = 0;
	int min = 2000000000;
	int current = this->head;
	while (current != NULL_TVALUE) {
		if (this->nodes[current].info.second < min) {
			min = this->nodes[current].info.second;
		}
		if (this->nodes[current].info.second > max) {
			max = this->nodes[current].info.second;
		}
		current = this->nodes[current].next;
	}
	return max - min;
}


SMIterator SortedMap::iterator() const //theta(1)
{
	return SMIterator(*this);
}


SortedMap::~SortedMap() //theta(1)
{
}
