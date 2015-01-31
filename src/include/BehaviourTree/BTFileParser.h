#ifndef _BTFileParser_h
#define _BTFileParser_h

#include "INode.h"

class BTFileParser
{
public:

	static BTFileParser* GetInstance();

	~BTFileParser();

	INode* ParseXMLFile(const char* filePath) const;

private:

	BTFileParser();

	static BTFileParser* instance;
};

#endif