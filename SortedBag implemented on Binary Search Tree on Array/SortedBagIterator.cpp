#pragma once
#include "pch.h"
#include "SortedBag.h"
#include "SortedBagIterator.h"


SortedBagIterator::SortedBagIterator(const SortedBag & _sb): sb{_sb} //theta(1)
{
	this->stack = std::stack<int>{};
	this->first();
}

void SortedBagIterator::first() //O(logn)
{
	this->current = this->sb.root;
	if (!this->stack.empty()) {
		while (!this->stack.empty()) {
			this->stack.pop();
		}
	}
	while (this->current != -1) {
		this->stack.push(this->current);
		current = this->sb.tree[this->current].left;
	}
	if (this->stack.empty() == false) {
		this->current = this->stack.top();
	}
	else {
		this->current = -1;
	}
}

void SortedBagIterator::next() //O(logn)
{
	if (this->valid() == false) {
		throw std::exception("");
	}
		int node = this->stack.top();
		this->stack.pop();
		if (this->sb.tree[node].right != -1) {
			node = this->sb.tree[node].right;
			while (node != -1) {
				this->stack.push(node);
				node = this->sb.tree[node].left;
			}
		}
		if (stack.empty() == false) {
			this->current = this->stack.top();
		}
		else {
			this->current = -1;
		}
}

bool SortedBagIterator::valid() const //theta(1)
{
	return this->current != -1;
}

TElem SortedBagIterator::getCurrent() const //theta(1)
{
	if (this->valid() == true) {
		return this->sb.tree[this->current].info;
	}
	else {
		throw std::exception("");
	}
}
