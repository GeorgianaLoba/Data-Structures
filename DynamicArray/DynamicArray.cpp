#pragma once
#include "DynamicArray.h"
#include "DAIterator.h"
#include <exception>


DynamicArray::DynamicArray(int capacity) //theta(1)
{
	this->length = 0;
	if (capacity > 0) {
		this->capacity = capacity;
	}
	else {
		throw std::exception ("The capacity needs to be a natural number");
	}
	this->elements = new TElem[this->capacity];
}


DynamicArray::~DynamicArray() //theta(1)
{
	delete[] this->elements;
}


int DynamicArray::size() const //theta(1)
{
	return this->length;
}

void DynamicArray::resize() //theta(n)
{
	this->capacity *= 2;
	TElem* newElements = new TElem[this->capacity];
	for (int index = 0; index < this->length; index++) {
		newElements[index] = this->elements[index];
	}
	delete[] this->elements;
	this->elements = newElements;
}

TElem DynamicArray::getElement(int pos) const //theta(1)
{
	if (pos < 0) {
		throw std::exception("indexing start at 0");
	}
	if (pos > this->length) {
		throw std::exception("there are not enough elements");
	}
	return this->elements[pos];
}

TElem DynamicArray::setElement(int pos, TElem newElem) //theta(1)
{
	TElem oldElement;
	if (pos < 0) {
		throw std::exception("indexing start at 0");
	}
	if (pos > this->length) {
		throw std::exception("there are not enough elements");
	}
	oldElement = this->elements[pos];
	this->elements[pos] = newElem;
	return oldElement;
}

void DynamicArray::addToEnd(TElem newElem) //BC: theta(1), WC: theta(n) <- should rarely enter the if!!!!!!!!!
{
	if (this->length == this->capacity) {
		this->resize();
	}
	this->elements[this->length++] = newElem;
}

void DynamicArray::addToPosition(int pos, TElem newElem) //theta(n)
{
	int index = 0;
	if (pos < 0) {
		throw std::exception("indexing start at 0");
	}
	if (pos > this->length) {
		throw std::exception("there are not enough elements");
	}
	this->length += 1;
	for (index = this->length; index > pos; index--) {
		this->elements[index] = this->elements[index-1];
	}
	this->elements[pos] = newElem;
}

TElem DynamicArray::remove(int pos) //o(n)
{
	TElem oldElem;
	int index;
	if (pos < 0) {
		throw std::exception("indexing start at 0");
	}
	if (pos > this->length) {
		throw std::exception("there are not enough elements");
	}
	oldElem = this->elements[pos];
	for (index = pos; index < this->length -1 ; index++) {
		this->elements[index] = this->elements[index+1];
	}
	this->length -= 1;
	return oldElem;
}

void DynamicArray::removeBetween(int i, int j)
{
	if (i < 0) {
		throw std::exception("indexing start at 0 in the array");
	}
	if (j > this->size()) {
		throw std::exception("indexing out of range, check the size");
	}
	for (int k = i; k < this->length - 1; k++) {
		this->elements[k] = this->elements[k + j-i];
	}
	this->length -= (j-i);
}

DAIterator DynamicArray::iterator() const
{
	return DAIterator(*this);
}

