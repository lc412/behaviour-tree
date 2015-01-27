#ifndef _sequence_h
#define _sequence_h

#include "Composite.h"

class Sequence : public Composite
{
public:

	Sequence(std::map<char*,void*>* sharedData);

	~Sequence();

	virtual void Init() override;

	virtual ProcessStatus::Enum Process() override;
};

#endif