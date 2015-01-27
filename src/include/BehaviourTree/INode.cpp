#include "INode.h"

INode::INode(std::map<char*,void*>* sharedData) 
: SharedData(sharedData) 
{
}

INode::~INode()
{
}
