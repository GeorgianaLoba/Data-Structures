#pragma once
#include "MultiMap.h"
#include "MultiMapIterator.h"


int MultiMap::TFunction(TKey k) //theta(1)
{
	int hash_position = k % this->capacity;
	if (hash_position > 0) {
		return hash_position;
	}
	else {
		return -hash_position;
	}
}

MultiMap::MultiMap() //theta(capacity)
{
	this->capacity = 13;
	this->firstEmpty = 0;
	this->lenght = 0;
	this->table = new TElem[this->capacity];
	this->next = new int[this->capacity];
	for (int i = 0; i < this->capacity; i++) {
		this->next[i] = -1;
		this->table[i].first = -1000000;
		this->table[i].second = -1000000;
	}
}

void MultiMap::add(TKey c, TValue v) //O(capacity*capacity)
{
	int pos = this->TFunction(c);
	if (this->lenght == this->capacity) {
		this->resize(); //thata(capacity)
		this->rehash(); //2 fors with thata(capacity) and then calls add capacity times
	}
	if (this->table[pos].first == -1000000) { //the hash pos is empty
		this->table[pos].first = c;
		this->table[pos].second = v;
		this->next[pos] = -1;
		this->lenght += 1;
	}
	else {
		this->table[this->firstEmpty].first = c; //we place it somewhere else and set the links
		this->table[this->firstEmpty].second = v;
		this->next[this->firstEmpty] = -1;
		while (this->next[pos] != -1) {
			pos = this->next[pos];
		}
		this->next[pos] = this->firstEmpty;
		this->lenght += 1;
	}
	if (this->table[firstEmpty].first != -1000000) {
		this->firstEmpty = this->resetFirstEmpty();
	}
}

bool MultiMap::remove(TKey c, TValue v) { //O(capacity)
	int i = this->TFunction(c);
	int j = -1;
	int idx = 0;
	while (idx < this->capacity && j == -1) {
		if (this->next[idx] == i){
			j = idx;
		}
		else {
			idx += 1;
		}
	}
	while (i != -1 && !(this->table[i].first == c && this->table[i].second ==v)) {
		j = i;
		i = this->next[i];
	}
	if (i == -1) {
		return false; //the (key, value) doesn't exist
	}
	else {
		bool over = false;
		int p;
		int pp;
		do {
			p = this->next[i];
			pp = i;
			while (p != -1 && this->TFunction(this->table[p].first) != i) {
				pp = p;
				p = this->next[p];
			}
			if (p == -1) {
				over = true;
			}
			else {
				this->table[i] = this->table[p];
				j = pp;
				i = p;
			}
		} while (!over);
		if (j != -1) {
			this->next[j] = this->next[i];
		}
		this->table[i].first = -1000000;
		this->table[i].second = -1000000;
		this->next[i] = -1;
		if (this->firstEmpty > i) {
			this->firstEmpty = i;
		}
		this->lenght = this->lenght - 1;
		return true;
	}
}

/*
bool MultiMap::remove(TKey c, TValue v)
{
	int pos = this->TFunction(c);
	if (this->next[pos] == -1) { //only one element with the wanted hash
		if (this->table[pos].first == c && this->table[pos].second == v) {
			this->table[pos].first = -1000000;
			this->table[pos].second = -1000000;
			this->next[pos] = -1;
			this->lenght -=1;
			this->firstEmpty = this->resetFirstEmpty();
			return true;
		}
		else {
			return false; //not found on the hash position
		}
	}
	else { //inside a list
		if (this->table[pos].first == c && this->table[pos].second == v) { //first elem in the list
			int current = pos;
			int previous = -1;
			while (this->next[current] != -1) {
				this->table[current].first = this->table[this->next[current]].first;
				this->table[current].second = this->table[this->next[current]].second;
				previous = current;
				current = this->next[current];
			}
			this->table[current].first = -1000000;
			this->table[current].second = -1000000;
			this->next[previous] = -1;
			this->next[current] = -1;
			this->firstEmpty = this->resetFirstEmpty();
			this->lenght -= 1;
			return true;
		}
		else {

			int current = pos;
			int previous = -1;
			while (current != -1 && !(this->table[current].first == c && this->table[current].second == v)) {
				previous = current;
				current = this->next[current];
			}
			if (current == -1) {
				return false;
			}
			this->next[previous] = this->next[current];
			this->next[current] = -1;
			this->table[current].first = -1000000;
			this->table[current].second = -1000000;
			this->lenght -= 1;
			this->firstEmpty = this->resetFirstEmpty();
			return true;
		}
	}
}
*/
std::vector<TValue> MultiMap::search(TKey c)  //O(capacity)
{
	std::vector<TValue> values;
	int pos= this->TFunction(c);
	while (pos != -1) {
		if (this->table[pos].first == c) {
			values.push_back(this->table[pos].second);
		}
		pos = this->next[pos];
	}
	return values;
}

int MultiMap::size() const //thata(1)
{
	return this->lenght;
}

bool MultiMap::isEmpty() const //thata(1)
{
	if (this->lenght == 0) {
		return true;
	}
	else {
		return false;
	}
}

void MultiMap::rehash() 
{	//not sure if its correct
	TElem* old_table = new TElem[this->capacity];
	for (int i = 0; i < this->capacity; i++) {
		old_table[i] = this->table[i];
	}
	int old_lenght = this->lenght;
	for (int i = 0; i < this->capacity; i++) {
		this->table[i].first = -1000000;
		this->table[i].second = -1000000;
		this->next[i] = -1;
	}
	this->firstEmpty = this->resetFirstEmpty();
	this->lenght = 0;
	for (int i = 0; i < old_lenght; i++) {
		this->add(old_table[i].first, old_table[i].second);
	}
}

void MultiMap::resize() //thata(capacity)
{
	TElem* new_table = new TElem[this->capacity * 2];
	int* new_next = new int[this->capacity * 2];
	for (int i=0; i < this->capacity; i++) {
		new_table[i] = this->table[i];
		new_next[i] = this->next[i];
	}
	for (int i = this->capacity; i < this->capacity * 2; i++) {
		new_table[i].first = -1000000;
		new_table[i].second = -1000000;
		new_next[i] = -1;
	}
	this->firstEmpty = this->capacity;
	this->capacity *= 2;
	delete[] this->table;
	delete[] this->next;
	this->table = new_table;
	this->next = new_next;
}

int MultiMap::resetFirstEmpty() //O(capacity)
{
	int pos = this->firstEmpty;
	if (this->table[pos].first == -1000000) {
		return pos;
	}
	else {
		for (int i = 0; i < this->capacity; i++) {
			if (this->table[i].first == -1000000) {
				return i;
			}
		}
	}
}

int MultiMap::addIfNotPresent(MultiMap & m) //O(m.capacity*)
{
	int addedPairs = 0;
	int cap= m.capacity;
	bool found;
	TKey currentKey;
	TValue currentValue;
	for (int i = 0; i < cap; i++) {
		currentKey = m.table[i].first;
		currentValue = m.table[i].second;
		found = false;
		int pos = this->TFunction(currentKey);
		while (pos != -1 && !found) {
			if (this->table[pos].first == currentKey && this->table[pos].second == currentValue) {
				found = true;
			}
			pos = this->next[pos];
		}
		if (!found) {
			this->add(currentKey, currentValue);
			addedPairs += 1;
		}
	}
	return addedPairs;

}

MultiMapIterator MultiMap::iterator() const //thata(capacity)
{
	return MultiMapIterator(*this);
}

MultiMap::~MultiMap() //thata(1)
{
	delete[] this->table;
	delete[] this->next;
}
