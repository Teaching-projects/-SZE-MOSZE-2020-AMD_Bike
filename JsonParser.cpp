#include "JsonParser.h"

std::map<std::string, std::string> JsonParser::Parser(std::string Data)
{
	std::map<std::string, std::string> toReturn;
	if (Data.rfind(".json") == Data.size()-5) {
		std::ifstream file;
		file.open(Data);
		std::string line;

		if (file.is_open()) {
			while (!file.eof()) {
				getline(file, line);
				Data += line;
			}
			file.close();
		}
		else {
			throw 1;
		}	
	}

	std::string akt2, akt1 = "";
	while (Data.find('"') != std::string::npos) {
		size_t x = Data.find('"') + 1;
		while (Data[x] != '"') {
			akt1 += Data[x];
			x++;
		}
		Data.erase(0, x + 1);
		if (akt1 == "name") {
			size_t x = Data.find('"') + 1;
			while (Data[x] != '"') {
				akt2 += Data[x];
				x++;
			}
			Data.erase(0, x + 1);
		}
		else {
			x = 0;
			while (isdigit(Data[x]) || akt2 == "") {
				if (isdigit(Data[x])) {
					akt2 += Data[x];
				}
				x++;
			}
			Data.erase(0, x + 1);
		}
		toReturn.insert(std::pair<std::string, std::string>(akt1, akt2));
		akt1 = "";
		akt2 = "";
	}
	return toReturn;
}

std::map<std::string, std::string> JsonParser::Parser(std::istream& Istream)
{
	std::string Data, line;
	while (std::getline(Istream, line))
	{
		Data += line;
	}
	return JsonParser::Parser(Data);
}
