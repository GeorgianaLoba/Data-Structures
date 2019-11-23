#pragma once
#include "SortedBag.h"


SortedBag::SortedBag(Relation r) //theta(1)
{
	this->head = NULL;
	this->rel = r;
}

void SortedBag::add(TComp e) //O(n)
{
	Node* currentNode = this->head;
	if (this->head == NULL) { //meaning that the list is empty, we want to add at the beginning
		Node* auxNode = new Node;
		auxNode->element = e;
		auxNode->frequency = 1;
		auxNode->next = this->head;
		this->head=auxNode; 
	}
	else {
		if (this->search(e) == true) { //the element is already present in the bag
			while (currentNode != NULL) { 
				if (currentNode->element == e) {
					currentNode->frequency += 1;
					break;
				}
				currentNode = currentNode->next;
			}
		}
		else {
			while (currentNode->next != NULL) {
				if (this->rel(currentNode->element, e) == false) {
					if (currentNode == this->head) {
						Node* auxNode = new Node;
						auxNode->element = e;
						auxNode->frequency = 1;
						auxNode->next = currentNode;
						this->head = auxNode;
						break;
					}
				}
				else if (this->rel(currentNode->next->element, e) == false) {
						Node* auxNode = new Node;
						auxNode->element = e;
						auxNode->frequency = 1;
						auxNode->next = currentNode->next;
						currentNode->next = auxNode;
						break;
				}
				currentNode = currentNode->next;
			}	
			if (currentNode->next==NULL){
					//inserting at the end of the bag
					Node* auxNode = new Node;
					auxNode->element = e;
					auxNode->frequency = 1;
					auxNode->next = NULL;
					currentNode->next = auxNode;
			}
		}
	}
}

bool SortedBag::remove(TComp e) //O(n)
{
	Node *currentNode = this->head;
	Node *prevNode = NULL;
	if (this->search(e) == true) {
		if (this->nrOccurrences(e) == 1) {
			while (currentNode != NULL && currentNode->element != e) {
				prevNode = currentNode;
				currentNode = currentNode->next;
			}
			if (currentNode != NULL && prevNode == NULL) {
				this->head = this->head->next;
			}
			else if (currentNode != NULL){
				prevNode->next = currentNode->next;
				currentNode->next = NULL;
			}	
		}
		else {
			while (currentNode != NULL) {
				//dunno if this one is oke
				if (currentNode->element == e) {
					currentNode->frequency -= 1;
					break;
				}
				currentNode = currentNode->next;
			}
		}
		return true;
	}
	else {
		return false;
	}
}

bool SortedBag::search(TComp e) const //O(n)
{
	Node* currentNode = this->head;
	while (currentNode != NULL) {
		if (currentNode->element == e) {
			return true;
		}
		currentNode=currentNode->next;
	}
	return false;
}


int SortedBag::nrOccurrences(TComp e) const //O(n)
{
	Node *currentNode = this->head;
	if (this->search(e) == true) {
		while (currentNode != NULL) {
			if (currentNode->element == e) {
				return currentNode->frequency;
			}
			currentNode = currentNode->next;
		}
	}
	else {
		return 0;
	}
}

int SortedBag::size() const //theta(n)
{
	int s = 0;
	Node *currentNode = this->head;
	while (currentNode != NULL) {
		s += currentNode->frequency;
		currentNode = currentNode->next;
	}
	return s;
}

bool SortedBag::isEmpty() const //theta(n)
{
	if (this->size() == 0) {
		return true;
	}
	else {
		return false;
	}
}

SortedBagIterator SortedBag::iterator() const //theta(1)
{
	return SortedBagIterator(*this);
}

SortedBag::~SortedBag()
{
}
