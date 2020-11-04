#ifndef JSONPARSER_H
#define JSONPARSER_H

#include <string>
#include <fstream>
#include <map>

class JsonParser {
public:
	static std::map<std::string, std::string> Parser(std::string FileName);
	static std::map<std::string, std::string> Parser(std::istream& Istream);
	static std::map<std::string, std::string> ParserFromString(std::string String);	
};

#endif
