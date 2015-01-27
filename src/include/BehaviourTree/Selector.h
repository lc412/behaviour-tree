#ifndef _selector_h
#define _selector_h

#include "Composite.h"

class Selector : public Composite
{
public:
	Selector(std::map<char*,void*>* sharedData);

	~Selector();

	virtual void Init() override;

	virtual ProcessStatus::Enum Process() override;
};

#endif