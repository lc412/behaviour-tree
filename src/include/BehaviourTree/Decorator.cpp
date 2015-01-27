#include "Decorator.h"

Decorator::Decorator(std::map<char*,void*>* sharedData)
: INode(sharedData)
{
}

Decorator::~Decorator()
{
}

void Decorator::SetChild(INode* child)
{
	this->child = child; 
}
