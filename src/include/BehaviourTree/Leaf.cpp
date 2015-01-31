#include "Leaf.h"
#include "../Lua/LuaManager.h"

Leaf::Leaf(std::map<char*,void*>* sharedData, std::string fn)
: INode(sharedData), LuaFnName(fn)
{
}

Leaf::~Leaf()
{
}

void Leaf::Init()
{
}

ProcessStatus::Enum Leaf::Process()
{
	return LuaManager::GetInstance()->CallLuaFunction(LuaFnName);
}
