#ifndef _inode_h
#define _inode_h

#include <map>

namespace ProcessStatus {
	enum Enum {
		Failure = 0,
		Running,
		Success
	};
}

class INode
{
public:
	INode(std::map<char*,void*>* sharedData);

	~INode();

	virtual void Init()=0;

	virtual ProcessStatus::Enum Process()=0;

protected:

	std::map<char*,void*>* SharedData;
};

#endif