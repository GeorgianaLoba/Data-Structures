#pragma once
#include <cstddef>

typedef int TElem;

class Node
{
public:
	TElem element;
	int frequency;
	Node* next;

	Node();
	Node(TElem el, int freq, Node* nxt);
	~Node();
};

