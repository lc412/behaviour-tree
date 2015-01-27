#include "Inverter.h"

Inverter::Inverter(std::map<char*,void*>* sharedData)
: Decorator(sharedData)
{
}

Inverter::~Inverter()
{
}

void Inverter::Init()
{
}

ProcessStatus::Enum Inverter::Process()
{
	ProcessStatus::Enum status = child->Process();

	if (status == ProcessStatus::Failure)
	{
		status = ProcessStatus::Success;
	}
	else if (status == ProcessStatus::Success)
	{
		status = ProcessStatus::Failure;
	}

	return status;
}