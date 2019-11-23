#include "SortedBagIterator.h"
#include <exception>


SortedBagIterator::SortedBagIterator(const SortedBag& otherBag): bag{otherBag}, currentNode{otherBag.head},currentFreq{1} //theta(1)
{
	
	/*this->currentNode = bag.head;
	this->currentFreq = 1;*/
}

void SortedBagIterator::first() //theta(1)
{
	this->currentNode = this->bag.head;
	this->currentFreq = 1;

}

void SortedBagIterator::next() //theta(1)
{
	if (this->valid() == false) {
		throw std::exception("Stop Iteration");
	}
	else {
		if (this->currentNode->frequency > this->currentFreq) { 
			this->currentFreq += 1;
		}
		else {
			this->currentNode = this->currentNode->next;
			this->currentFreq = 1;
		}
	}
}
 
bool SortedBagIterator::valid() const //theta(1)
{
	if (this->currentNode == NULL) {
		return false;
	}
	return true;
}

TElem SortedBagIterator::getCurrent() const //theta(1)
{
	if (this->valid() == true) {
		return this->currentNode->element;
	}
	else {
		throw std::exception("No current");
	}
}

SortedBagIterator::~SortedBagIterator()
{
}
