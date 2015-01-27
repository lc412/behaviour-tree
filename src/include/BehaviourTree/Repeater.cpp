#include "Repeater.h"

Repeater::Repeater(std::map<char*,void*>* sharedData, bool untilFailure)
: Decorator(sharedData), repeatUntilFailure(untilFailure)
{
}

Repeater::~Repeater()
{
}

void Repeater::Init()
{
}

ProcessStatus::Enum Repeater::Process()
{
	ProcessStatus::Enum childStatus = child->Process();

	return (repeatUntilFailure && childStatus == ProcessStatus::Failure)
		? ProcessStatus::Failure : ProcessStatus::Running;
}