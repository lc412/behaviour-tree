#ifndef _succeeder_h
#define _succeeder_h

#include "Decorator.h"

class Succeeder final : public Decorator
{
public:
	Succeeder(std::map<char*,void*>* sharedData);

	~Succeeder();

	virtual void Init() override;

	virtual ProcessStatus::Enum Process() override;
};

#endif