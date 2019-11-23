#pragma once
#include "Node.h"


Node::Node()
{
	this->element = NULL;
	this->frequency = NULL;
	this->next = NULL;
}
Node::Node(TElem el, int freq, Node* nxt): element{el}, frequency{freq}, next{nxt}
{
}
Node::~Node()
{
}
