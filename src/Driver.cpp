#include "include/BehaviourTree/INode.h"
#include "include/BehaviourTree/Sequence.h"

#include "include/BehaviourTree/BTFileParser.h"

#include <iostream>
#include <map>

int main(int argc, char* argv[])
{
	std::map<char*,void*>* sharedData = new std::map<char*,void*>();

	BTFileParser* fileParser = BTFileParser::GetInstance();

	fileParser->SetSharedData(sharedData);

	INode* root = fileParser->ParseXMLFile("./input/test.xml");

	ProcessStatus::Enum result = root->Process();

	std::cout << "Final status: ";

	switch(result) {
		case ProcessStatus::Failure:
			std::cout << "Failed" << std::endl;
			break;
		case ProcessStatus::Running:
			std::cout << "Running" << std::endl;
			break;
		case ProcessStatus::Success:
			std::cout << "Success" << std::endl;
			break;
	}

	delete static_cast<Sequence*>(root);
	delete sharedData;

	return 0;
}
