#ifndef _composite_h
#define _composite_h

#include "INode.h"
#include <vector>

class Composite : public INode
{
public:
	
	Composite(std::map<char*,void*>* sharedData);

	~Composite();

	virtual void Init()=0;

	virtual ProcessStatus::Enum Process()=0;

	void AddChild(INode* child);

protected:

	std::vector<INode*> children;
};

#endif