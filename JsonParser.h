/**
* \class JsonParser
*
* \brief JsonParser class
*
* This class's role is, to prepare the Character class's parseUnit() function for 3 types of input. These input's are the istream, filename and string.
*
* \author skrobi12, hajdunorbi, Szabi1104
*
* \version 3.0
*
* \date 2020/11/01 19:17
*/

#ifndef JSONPARSER_H
#define JSONPARSER_H

#include <string>
#include <fstream>
#include <map>

class JsonParser {
public:
	/**
	* \brief This function opens the given input (in the current case a FileName). After a FileName is given, this function makes a string from it, and calls the ParserFromString() function, whit the created string as parameter.
	* \param FileNam
	* \return Returns a <string, string> type map, which contains all the necessary data, what a Player, or Character has.
	*
	*/
	static std::map<std::string, std::string> Parser(std::string FileName);
	/**
	* \brief This function opens the given input (in the current case an Istream). After an Istream is given, this function makes a string from it, and calls the ParserFromString() function, whit the created string as parameter.
	* \param Istream
	* \return Returns a <string, string> type map, which contains all the necessary data, what a Player, or Character has.
	*
	*/
	static std::map<std::string, std::string> Parser(std::istream& Istream);
	/**
	* \brief This function gets a String as an argument, or from the listed functions before. Then the function loads the parameters, which it gets from the String, into a Map, and returns this Map. 
	* \param String
	* \return Returns a <string, string> type map, which contains all the necessary data, what a Player, or Character has.
	*
	*/
	static std::map<std::string, std::string> ParserFromString(std::string String);	
};

#endif
