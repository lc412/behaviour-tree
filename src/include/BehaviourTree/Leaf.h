#ifndef _leaf_h
#define _leaf_h

#include "INode.h"

class Leaf final : public INode
{
public:
	Leaf(std::map<char*,void*>* sharedData, const char* fn);

	~Leaf();

	virtual void Init() override;

	virtual ProcessStatus::Enum Process() override;

private:
	const char* LuaFnName;
};

#endif