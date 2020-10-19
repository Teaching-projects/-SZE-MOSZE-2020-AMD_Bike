#include "JsonParser.h"

std::map<std::string, std::string> JsonParser::ParserForFileName(std::string FileName)
{
	if (FileName.rfind(".json") == FileName.size() - 5) {
		std::ifstream file;
		file.open(FileName);
		std::string line;

		if (file.is_open()) {
			while (getline(file, line)) {
				FileName += line;
			}
			file.close();
		}
		else {
			throw 1;
		}
	}
	return JsonParser::ParserForString(FileName);
}
	
std::map<std::string, std::string> JsonParser::ParserForIstream(std::istream& Istream)
{
	std::string Data, line;
	while (getline(Istream, line))
	{
		Data += line;
	}
	return JsonParser::ParserForString(Data);
}

std::map<std::string, std::string> JsonParser::ParserForString(std::string String)
{
	std::map<std::string, std::string> toReturn;
	std::string akt2, akt1 = "";
	char sign = '"';
	while (String.find(sign) != std::string::npos) {
		size_t x = String.find(sign) + 1;
		if (x == String.rfind(sign) - 1) {
			sign = ' ';
		}
		while (String[x] != sign) {
			akt1 += String[x];
			x++;
		}
		String.erase(0, x + 1);
		if (akt1 == "name") {
			size_t x = String.find(sign) + 1;
			while (String[x] != sign) {
				akt2 += String[x];
				x++;
			}
			String.erase(0, x + 1);
		}
		else {
			x = 0;
			while (isdigit(String[x]) || akt2 == "") {
				if (isdigit(String[x])) {
					akt2 += String[x];
				}
				x++;
			}
			String.erase(0, x + 1);
		}
		toReturn.insert(std::pair<std::string, std::string>(akt1, akt2));
		akt1 = "";
		akt2 = "";
	}
	return toReturn;
}