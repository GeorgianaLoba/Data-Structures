#pragma once
#include "SMIterator.h"

SMIterator::SMIterator (const SortedMap& othersm): sm{othersm},currentElem{othersm.head} //theta(1)
{
}

void SMIterator::first() { //theta(1)
	this->currentElem = this->sm.head;
}

void SMIterator::next() { //theta(1)
	if (this->valid()) {
		this->currentElem = this->sm.nodes[currentElem].next;
	}
	else {
		throw std::exception("Stop Iteration\n");
	}
}

bool SMIterator::valid() const { //theta(1)
	if (this->currentElem != NULL_TVALUE) {
		return true;
	}
	else {
		return false;
	}
}

TElem SMIterator::getCurrent() const { //theta(1)
	if (this->valid()) {
		return this->sm.nodes[this->currentElem].info;
	}
	else {
		throw std::exception("invalid element\n");
	}
}


SMIterator::~SMIterator() //theta(1)
{
}
