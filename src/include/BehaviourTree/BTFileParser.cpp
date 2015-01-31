#include "BTFileParser.h"
#include "./../RapidXML/rapidxml.hpp"

#include <string>
#include <fstream>
#include <sstream>

BTFileParser* BTFileParser::instance = nullptr;

BTFileParser BTFileParser::GetInstance()
{
	if (instance == nullptr)
	{
		instance = new BTFileParser();
	}	
	return instance;
}

BTFileParser::BTFileParser()
{
}

BTFileParser::~BTFileParser()
{
	delete instance;
}

INode* ParseXMLFile(const char* filePath)
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
	xml_node<>* rootNode = doc.first_node();

	// TODO: parse all text
}