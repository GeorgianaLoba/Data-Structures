#include "Node.h"



Node::Node()
{
}

Node::Node(TElem inf, int nxt, int prv) : info{ inf }, next{ nxt }, prev{ prv }
{

}

Node::~Node()
{
}
