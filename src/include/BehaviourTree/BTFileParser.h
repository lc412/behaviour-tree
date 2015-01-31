#ifndef _BTFileParser_h
#define _BTFileParser_h

#include "INode.h"

#include <map>

class BTFileParser
{
public:

	static BTFileParser* GetInstance();

	~BTFileParser();

	INode* ParseXMLFile(const char* filePath);

	std::map<char*,void*>* GetSharedData();

	void SetSharedData(std::map<char*,void*>* sharedData);

private:

	BTFileParser();

	static BTFileParser* instance;

	std::map<char*,void*>* sharedData;
};

#endif