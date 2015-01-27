#ifndef _inverter_h
#define _inverter_h

#include "Decorator.h"

class Inverter final : public Decorator
{
public:

	Inverter(std::map<char*,void*>* sharedData);

	~Inverter();

	virtual void Init() override;

	virtual ProcessStatus::Enum Process() override;
};

#endif