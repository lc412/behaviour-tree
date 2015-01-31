#include "BTFileParser.h"
#include "./../RapidXML/rapidxml.hpp"

#include "NodeTypes.h"
#include "Composite.h"
#include "Decorator.h"
#include "Leaf.h"
#include "Sequence.h"
#include "Selector.h"
#include "Inverter.h"
#include "Repeater.h"
#include "Succeeder.h"

#include <string>
#include <fstream>
#include <sstream>

#include <cstring>

#include <iostream>

#define STRCMP_EQUAL 0

using namespace rapidxml;

/* Interface */

static NodeType::Enum DetermineNodeType(xml_node<>* node);

static INode* ConstructBTNodeFromXMLNode(xml_node<>* node, std::map<char*,void*>* sharedData);

static void ParseXMLSubTree(xml_node<>* subTreeRoot, INode* parent, NodeType::Enum parentType, std::map<char*,void*>* sharedData);

/* Implementation */

BTFileParser* BTFileParser::instance = nullptr;

BTFileParser* BTFileParser::GetInstance()
{
	if (instance == nullptr)
	{
		instance = new BTFileParser();
	}	
	return instance;
}

BTFileParser::BTFileParser()
{
	sharedData = nullptr;
}

BTFileParser::~BTFileParser()
{
	delete instance;
}

std::map<char*,void*>* BTFileParser::GetSharedData()
{
	return sharedData;
}

void BTFileParser::SetSharedData(std::map<char*,void*>* sharedData)
{
	this->sharedData = sharedData;
}

INode* BTFileParser::ParseXMLFile(const char* filePath)
{
	const uint INITIAL_TEXT_INDEX = 0;
	const int PARSE_FLAGS = 0; // 0 signals default parse settings

	// Retrieve XML text
	std::ifstream t(filePath);
	std::stringstream buffer;
	buffer << t.rdbuf();
	std::string text = buffer.str();

	// Initialise XML parser
	xml_document<> doc;
	doc.parse<0>(&text[INITIAL_TEXT_INDEX]);

	// Parse XML text
	xml_node<>* rootXMLNode = doc.first_node();

	INode* root = new Sequence(sharedData);

	if (rootXMLNode != nullptr)
	{
		ParseXMLSubTree(rootXMLNode->first_node(), root, NodeType::Composite, 
			sharedData);
	}

	return root;
}

NodeType::Enum DetermineNodeType(xml_node<>* node)
{
	char* name = node->name();

	NodeType::Enum type;
	if (!strcmp(name, "sequence") 
		|| !strcmp(name, "selector"))
	{
		type = NodeType::Composite;
	}	
	else if (!strcmp(name, "repeater") 
			 || !strcmp(name, "succeeder") 
			 || !strcmp(name, "inverter"))
	{
		type = NodeType::Decorator;
	}
	else if (!strcmp(name, "leaf"))
	{
		type = NodeType::Leaf;
	}
	else
	{
		// TODO: throw error.
		std::cout << "Error: Node doesn't have a valid type." << std::endl;
	}

	return type;
}

INode* ConstructBTNodeFromXMLNode(xml_node<>* node, std::map<char*,void*>* sharedData)
{
	INode* btNode = nullptr;

	char* name = node->name();
	if (!strcmp(name, "sequence"))
	{
		btNode = new Sequence(sharedData);
	}
	else if (!strcmp(name, "selector"))
	{
		btNode = new Selector(sharedData);
	}	
	else if (!strcmp(name, "repeater"))
	{
		xml_attribute<>* repeaterEndAttribute = 
			node->first_attribute("repeatUntilFailure");
		if (repeaterEndAttribute != nullptr)
		{
			bool untilFailure;
			std::string repeatFlag = repeaterEndAttribute->value();
			if (!repeatFlag.compare("true"))
			{
				untilFailure = true;
			}
			else if (!repeatFlag.compare("false"))
			{
				untilFailure = false;
			}
			else
			{
				// TODO: throw error.
				std::cout << "Error: invalid repeater attribute." << std::endl;
			}

			btNode = new Repeater(sharedData, untilFailure);
		}
		else
		{
			// TODO: throw error.
			std::cout << "Error: repeater node doesn't have proper attributes." 
					  << std::endl;
		}
	}
	else if (!strcmp(name, "succeeder"))
	{
		btNode = new Succeeder(sharedData);
	}
	else if (!strcmp(name, "inverter"))
	{
		btNode = new Inverter(sharedData);
	}
	else if (!strcmp(name, "leaf"))
	{
		xml_attribute<>* leafFnAttribute = node->first_attribute("fn");
		if (leafFnAttribute != nullptr)
		{
			std::string test = leafFnAttribute->value();
			btNode = new Leaf(sharedData, test);
		}
		else
		{
			// TODO: throw error.
			std::cout << "Error: leaf node doesn't have proper attributes." 
					  << std::endl;
		}
	}
	else
	{
		// TODO: throw error.
		std::cout << "Error: Node doesn't have a valid type." << std::endl;
	}

	return btNode;	
}

void ParseXMLSubTree(xml_node<>* subTreeRoot, INode* parent, 
	NodeType::Enum parentType, std::map<char*,void*>* sharedData)
{
	xml_node<>* currentNode = subTreeRoot;
	xml_node<>* currentNodeFirstChild = nullptr;
	NodeType::Enum currentNodeType;

	do {
		// determine node type
		currentNodeType = DetermineNodeType(currentNode);

		// construct node given xml node
		INode* treeNode = 
			ConstructBTNodeFromXMLNode(currentNode, sharedData);
			
		// Add constructed node as children to parent
		switch (parentType)
		{
			case NodeType::Composite:
				static_cast<Composite*>(parent)->AddChild(treeNode);
				break;

			case NodeType::Decorator:
				static_cast<Decorator*>(parent)->SetChild(treeNode);
				break;

			default:
				break;
		}

		// if not leaf node, parse XML subtree
		if (currentNodeType != NodeType::Leaf)
		{
			currentNodeFirstChild = currentNode->first_node();
			if (currentNodeFirstChild == nullptr)
			{
				// TODO: throw error.
				std::cout << "Error: node should have child!" << std::endl;
				return;
			}

			ParseXMLSubTree(currentNodeFirstChild, treeNode, currentNodeType, sharedData);
		}

		// retrieve next child
		currentNode = currentNode->next_sibling();

	} while (currentNode != nullptr);
}
