#include "Succeeder.h"

Succeeder::Succeeder(std::map<char*,void*>* sharedData)
: Decorator(sharedData)
{
}

Succeeder::~Succeeder()
{
}

void Succeeder::Init()
{
}

ProcessStatus::Enum Succeeder::Process()
{
	child->Process();
	return ProcessStatus::Success;
}