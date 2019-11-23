#pragma once
#include "pch.h"
#include "SortedBag.h"
#include "SortedBagIterator.h"


SortedBag::SortedBag(Relation r) : rel{ r } //theta(1)
{
	this->root = -1;
	this->lenght = 0;
	this->capacity = 16;
	this->tree = new Node[this->capacity];
	this->firstEmpty = 0;
	for (int i = 0; i < this->capacity-1; i++) {
		this->tree[i].left = i + 1;
	}
	this->tree[this->capacity - 1].left = -1;

}

void SortedBag::resetFirstEmpty() //O(capacity)
{
	//guess it will work but this is not how it's said to be done in the lecture
	/*this->firstEmpty = 0;
	while (this->firstEmpty < this->capacity && !(this->tree[firstEmpty].isNull())){
		this->firstEmpty += 1;
	}*/

	this->firstEmpty = this->tree[this->firstEmpty].left;
	if (!this->tree[this->firstEmpty].isNull()) {
		while (this->firstEmpty != -1) {
			this->firstEmpty = this->tree[this->firstEmpty].left;
		}
	}
}



void SortedBag::resize() //theta(capacity)
{
	Node* newTree = new Node[this->capacity * 2];
	for (int i = 0; i < this->capacity; i++) {
		newTree[i].info = this->tree[i].info;
		newTree[i].right = this->tree[i].right;
		newTree[i].left = this->tree[i].left;
	}
	delete[] this->tree;
	this->tree = newTree;
	//this->firstEmpty = this->capacity;
	for (int i = this->capacity; i < this->capacity * 2; i++) {
		this->tree[i].left = i + 1;
	}
	this->tree[this->capacity * 2 - 1].left = -1;
	this->capacity *= 2;
}

TComp SortedBag::getMinimum(int startingRoot) //theta(log(n))
{
	int currentN = startingRoot;
	int minimumN = startingRoot;
	TComp minValue;
	while (currentN != -1) {
		minValue = this->tree[currentN].info;
		minimumN = currentN;
		currentN = this->tree[currentN].left;
	}
	return minimumN;
}

TComp SortedBag::getMaximum(int startingRoot) //theta(log(n))
{
	int currentN = startingRoot;
	int maximumN = startingRoot;
	TComp maxValue;
	while (currentN != -1) {
		maxValue = this->tree[currentN].info;
		maximumN = currentN;
		currentN = this->tree[currentN].right;
	}
	return maximumN;
}
int SortedBag::removeRecursively(int node, TComp e, bool & removed) //theta(O(n)) < n is the number of pairs
{
	if (node == -1) {
		return node;
	}
	if (e == this->tree[node].info) {
		removed = true;
		if (this->tree[node].left == -1) {
			int rightChild = this->tree[node].right;
			this->tree[node] = Node{};
			return rightChild;
		}
		else if(this->tree[node].right==-1){
			int leftChild = this->tree[node].left;
			this->tree[node] = Node{};
			return leftChild;
		}
		else {
			int maxN = this->getMaximum(this->tree[node].left);
			this->tree[node].info = this->tree[maxN].info;
			this->tree[node].left = this->removeRecursively(this->tree[node].left, this->tree[maxN].info, removed);
		}
	}
	else if (this->rel(e, this->tree[node].info)) {
		this->tree[node].left = this->removeRecursively(this->tree[node].left, e, removed);
	}
	else {
		this->tree[node].right = this->removeRecursively(this->tree[node].right, e, removed);
	}
	return node;
}
void SortedBag::add(TComp e) //theta(logn) <= n is the nr of elements
{
	if (this->firstEmpty >= this->capacity) {
		this->resize(); //amortizat
	}
	int newEmpty = this->tree[this->firstEmpty].left;
	this->tree[this->firstEmpty].info = e;
	this->tree[this->firstEmpty].left = -1;
	this->tree[this->firstEmpty].right = -1;
	int current = this->root;
	int parent = -1;
	while (current != -1) {
		parent = current;
		if (this->rel(e, this->tree[current].info) == true) {
			current = this->tree[current].left;
		}
		else {
			current = this->tree[current].right;
		}
	}
	if (this->root == -1) { //the case in which we don't have a root
		this->root = this->firstEmpty;
	}
	else if (this->rel(e, this->tree[parent].info)) { 
		this->tree[parent].left = this->firstEmpty;
	}
	else {
		this->tree[parent].right = this->firstEmpty;
	}
	this->firstEmpty = newEmpty;
	this->lenght += 1;
}

bool SortedBag::remove(TComp e) //o(logn)
{
	//wrapper function
	bool removed = false;
	this->root = this->removeRecursively(this->root, e, removed);
	if (removed) {
		this->lenght -= 1;
	}

	return removed;
}

bool SortedBag::search(TComp e) const //O(logn)
{
	int currentN = this->root;
	while (currentN != -1) {
		if (this->tree[currentN].info == e) {
			return true;
		}
		if (this->rel(e, this->tree[currentN].info)) {
			currentN = this->tree[currentN].left;
		}
		else {
			currentN = this->tree[currentN].right;
		}
	}
	return false;
}

int SortedBag::nrOccurrences(TComp e) const //O(logn)
{
	int currentN = this->root;
	int number = 0;
	while (currentN != -1) {
		if (this->tree[currentN].info == e) {
			number += 1;
		}
		if (this->rel(e, this->tree[currentN].info)) {
			currentN = this->tree[currentN].left;
		}
		else {
			currentN = this->tree[currentN].right;
		}
	}
	return number;
}



int SortedBag::size() const //theta(1)
{
	return this->lenght;
}

SortedBagIterator SortedBag::iterator() const
{
	return SortedBagIterator(*this);
}

bool SortedBag::isEmpty() const //theta(1)
{
	if (this->lenght == 0) {
		return true;
	}
	else {
		return false;
	}
}

void SortedBag::empty() //theta(n)
{
	std::queue<TComp> depthTraversal;
	int toBeRemoved = this->root;
	if (!this->isEmpty()) {
		depthTraversal.push(toBeRemoved);
		while (!depthTraversal.empty()) {
			int left = this->tree[toBeRemoved].left;
			int right = this->tree[toBeRemoved].right;
			if (left != -1) {
				depthTraversal.push(left);
			}
			if (right!=-1) {
				depthTraversal.push(right);
			}

			this->tree[toBeRemoved] = Node{};
			this->lenght -= 1;
			depthTraversal.pop();
			if (!depthTraversal.empty()) {
				toBeRemoved = depthTraversal.front();
			}
		}
	}
	//this->resetFirstEmpty();
	for (int i = 0; i < this->capacity - 1; i++) {
		this->tree[i].left = i + 1;
	}
	this->tree[this->capacity - 1].left = -1;
	this->root = -1;
	
}

SortedBag::~SortedBag() //theta(1)
{
	delete[] this->tree;
}
