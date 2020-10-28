#include "JsonParser.h"

std::map<std::string, std::string> JsonParser::Parser(std::string FileName)
{
	std::ifstream file;
	file.open(FileName);
	std::string line;

	if (file.is_open()) {
		while (getline(file, line)) {
			FileName += line;
		}
		file.close();
	}
	return JsonParser::ParserFromString(FileName);
}
	
std::map<std::string, std::string> JsonParser::Parser(std::istream& Istream)
{
	std::string Data, line;
	while (getline(Istream, line))
	{
		Data += line;
	}
	return JsonParser::ParserFromString(Data);
}

std::map<std::string, std::string> JsonParser::ParserFromString(std::string String)
{
	std::map<std::string, std::string> toReturn;
	std::string akt2, akt1 = "";
	char sign = '"';
	while (String.find(sign) != std::string::npos) {
		size_t x = String.find(sign) + 1;
		if (x == String.rfind(sign) - 1) {
			sign = ' ';
		}
		while ((String[x] != sign) && (x!=String.size())) {
			akt1 += String[x];
			x++;
		}
		String.erase(0, x + 1);
		if (akt1 == "name") {
			size_t x = String.find(sign) + 1;
			while ((String[x] != sign) && (x != String.size())) {
				akt2 += String[x];
				x++;
			}
			String.erase(0, x + 1);
		}
		else {
			x = 0;
			while ((isdigit(String[x]) || akt2 == "") && (x != String.size())) {
				if (isdigit(String[x])) {
					akt2 += String[x];
				}
				x++;	
			}
			while ((String[x+1] <= String.size()) && (String[x+1] != '"') && (String[x + 1] != ',')) {
				if (isdigit(String[x + 1])) {
					throw std::runtime_error("Only digit adat is acceptable!");
				}
				x++;
			}
			String.erase(0, x + 1);
		}
		toReturn.insert(std::pair<std::string, std::string>(akt1, akt2));
		akt1 = "";
		akt2 = "";
	}
	if (toReturn.size() != 3) {
		throw std::runtime_error("Not enough parameters!");
	}
	return toReturn;
}