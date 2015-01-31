#ifndef _decorator_h
#define _decorator_h

#include "INode.h"

class Decorator : public INode
{
public:
	Decorator(std::map<char*,void*>* sharedData);

	~Decorator();

	virtual void Init()=0;

	virtual ProcessStatus::Enum Process()=0;

	INode* GetChild();

	void SetChild(INode* child);

protected:

	INode* child;
};

#endif