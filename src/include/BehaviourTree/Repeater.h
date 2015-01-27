#ifndef _repeater_h
#define _repeater_h

#include "Decorator.h"

class Repeater : public Decorator
{
public:
	Repeater(std::map<char*,void*>* sharedData, bool untilFailure);

	~Repeater();

	virtual void Init() override;

	virtual ProcessStatus::Enum Process() override;

private:

	bool repeatUntilFailure;
};

#endif