#include "pch.h"
#include "node.h"


Node::Node()
{
	this->info = null_TElem;
	this->left = -1;
	this->right = -1;
}

Node::Node(TElem _info, int _left, int _right): info{_info}, left{_left}, right{_right}
{
}

bool Node::isNull()
{
	bool null = true;
	if (this->info != null_TElem) {
		null = false;
	}
	if (this->right != -1) {
		null = false;
	}
	if (this->left != -1) {
		null = false;
	}
	return null;
}

Node::~Node()
{
}
