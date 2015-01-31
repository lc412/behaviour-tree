#include "Leaf.h"
//#include <iostream>
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
	//std::cout << "Processed!" << std::endl;
	
	LuaManager::GetInstance()->CallLuaFunction(LuaFnName);

	int* data = static_cast<int*>(SharedData->at("processedCount"));
	(*data)++;
	return ProcessStatus::Success;
}
