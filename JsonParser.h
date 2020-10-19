#ifndef JSONPARSER_H
#define JSONPARSER_H

#include <string>
#include <fstream>
#include <map>

class JsonParser {
public:
	static std::map<std::string, std::string> ParserForFileName(std::string FileName);
	static std::map<std::string, std::string> ParserForIstream(std::istream& Istream);
	static std::map<std::string, std::string> ParserForString(std::string String);	
};

#endif
