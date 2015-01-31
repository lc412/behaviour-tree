#include "Decorator.h"

Decorator::Decorator(std::map<char*,void*>* sharedData)
: INode(sharedData), child(nullptr)
{
}

Decorator::~Decorator()
{
}

INode* Decorator::GetChild()
{
	return child;
}

void Decorator::SetChild(INode* child)
{
	this->child = child; 
}
