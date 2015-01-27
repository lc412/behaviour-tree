#include "Composite.h"

Composite::Composite(std::map<char*,void*>* sharedData)
: INode(sharedData)
{
}

Composite::~Composite()
{
}

void Composite::AddChild(INode* child)
{
	children.push_back(child);
}