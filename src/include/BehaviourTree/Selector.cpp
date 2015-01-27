#include "Selector.h"

Selector::Selector(std::map<char*,void*>* sharedData)
: Composite(sharedData)
{
}

Selector::~Selector()
{
}

void Selector::Init()
{
}

ProcessStatus::Enum Selector::Process()
{
	ProcessStatus::Enum status = ProcessStatus::Failure;

	for (auto it = children.begin(); it != children.end(); it++)
	{
		status = (*it)->Process();
		if (status == ProcessStatus::Success 
			|| status == ProcessStatus::Running)
		{
			break;
		}
	}
	
	return status;
}
