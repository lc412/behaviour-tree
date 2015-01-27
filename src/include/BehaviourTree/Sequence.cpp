#include "Sequence.h"

Sequence::Sequence(std::map<char*,void*>* sharedData)
: Composite(sharedData)
{
}

Sequence::~Sequence()
{
}

void Sequence::Init()
{
}

ProcessStatus::Enum Sequence::Process()
{
	ProcessStatus::Enum status = ProcessStatus::Success;

	for (auto it = children.begin(); it != children.end(); it++)
	{
		status = (*it)->Process();
		if (status == ProcessStatus::Failure 
			|| status == ProcessStatus::Running)
		{
			break;
		}
	}

	return status;
}