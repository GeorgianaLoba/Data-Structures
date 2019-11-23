#pragma once


#include "pch.h"
const int null_TElem = -999999999;
typedef int TComp;
typedef TComp TElem;

class Node
{
public:
	TElem info;
	int left;
	int right;
	Node();
	Node(TElem info, int left, int right);
	bool isNull();
	~Node();
};

