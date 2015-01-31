#include "include/BehaviourTree/INode.h"

#include "include/BehaviourTree/Leaf.h"

#include "include/BehaviourTree/Composite.h"
#include "include/BehaviourTree/Sequence.h"
#include "include/BehaviourTree/Selector.h"

#include "include/BehaviourTree/Decorator.h"
#include "include/BehaviourTree/Inverter.h"
#include "include/BehaviourTree/Succeeder.h"
#include "include/BehaviourTree/Repeater.h"

#include "include/Lua/LuaManager.h"

#include "include/BehaviourTree/BTFileParser.h"

#include <iostream>
#include <map>

#include <string>
#include <fstream>
#include <sstream>

int main(int argc, char* argv[])
{
	std::map<char*,void*>* sharedData = new std::map<char*,void*>();

	BTFileParser* fileParser = BTFileParser::GetInstance();

	fileParser->SetSharedData(sharedData);

	INode* root = fileParser->ParseXMLFile("./input/test.xml");

	ProcessStatus::Enum result = root->Process();

	delete static_cast<Sequence*>(root);
	delete sharedData;

////////////////////////////////////////////////////////////

	// // Retrieve XML text
	// std::ifstream t("./input/test.xml");
	// std::stringstream buffer;
	// buffer << t.rdbuf();
	// std::string text = buffer.str();

	// // parse XML document
	// const int PARSE_FLAGS = 0; // 0 signals default parse settings
	// xml_document<> doc;
	// doc.parse<0>(&text[0]);

	// xml_node<>* currentNode = doc.first_node();


	// std::map<char*,void*>* sharedData = new std::map<char*,void*>();

	// int processedCount = 0;
	// (*sharedData)["processedCount"] = &processedCount;

	// Composite* root = new Sequence(sharedData); // memory leak

	// // manually retrieve leaf nodes (test code)
	// xml_node<>* leafNode = currentNode->first_node();
	// while (leafNode != nullptr)
	// {
	// 	xml_attribute<>* leafNodeAttr = leafNode->first_attribute();
	// 	char* leafNodeFn = leafNodeAttr->value();
	// 	root->AddChild(new Leaf(sharedData, leafNodeFn));

	// 	leafNode = leafNode->next_sibling();
	// }

	// //root->AddChild(new Leaf(sharedData, leafNodeFn)); // memory leak

	// ProcessStatus::Enum result = root->Process();

////////////////////////////////////////////////////////////

	// const char* luaFunctionNameLeaf = "display";

	// std::map<char*,void*>* sharedData = new std::map<char*,void*>();

	// int processedCount = 0;
	// (*sharedData)["processedCount"] = &processedCount;

	// Composite* root = new Sequence(sharedData);

	// const unsigned int LEAF_COUNT = 10;
	// for (unsigned int i = 0; i < LEAF_COUNT; i++)
	// {
	// 	root->AddChild(new Leaf(sharedData, luaFunctionNameLeaf)); // memory leak
	// }

	// Selector* subSelector = new Selector(sharedData);
	// root->AddChild(subSelector);
	// for (unsigned int i = 0; i < LEAF_COUNT; i++)
	// {
	// 	subSelector->AddChild(new Leaf(sharedData, luaFunctionNameLeaf)); // memory leak
	// }

	// Inverter* inverter = new Inverter(sharedData);
	// inverter->SetChild(new Leaf(sharedData, luaFunctionNameLeaf)); // memory leak
	// root->AddChild(static_cast<INode*>(inverter));

	// ProcessStatus::Enum result = root->Process();

	// delete inverter;
	// delete subSelector;
	// delete sharedData;

////////////////////////////////////////////////////////////

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

	return 0;
}
