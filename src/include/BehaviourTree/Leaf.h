#ifndef _leaf_h
#define _leaf_h

#include "INode.h"
#include <string>

class Leaf final : public INode
{
public:
	Leaf(std::map<char*,void*>* sharedData, std::string fn);

	~Leaf();

	virtual void Init() override;

	virtual ProcessStatus::Enum Process() override;

private:
	std::string LuaFnName;
};

#endif