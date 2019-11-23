#pragma once
#include <utility>

typedef int TKey;
typedef int TValue;
typedef std::pair<TKey, TValue> TElem;


class Node
{
public:
	TElem info;
	int next;
	int prev;
	Node();
	Node(TElem inf, int nxt, int prv);
	~Node();
};

