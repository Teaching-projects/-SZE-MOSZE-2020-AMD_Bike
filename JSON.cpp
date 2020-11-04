#include "JSON.h"
#include <iostream>

JSON::JSON(std::map<std::string, std::string> scenario) : scenario(scenario)
{
}

JSON JSON::parseFromFile(std::string FileName)
{
	std::ifstream file;
	file.open(FileName);
	std::string Data, line;

	if (file.is_open()) {
		while (getline(file, line)) {
			Data += line;
		}
		file.close();
	}
	else {
		std:: string errMsg = "The file cannot be opened!";
		throw ParseException(errMsg);
	}

	return parseFromString(Data);
}

JSON JSON::parseFromFile(std::istream Istream)
{
	std::string Data, line;
	while (getline(Istream, line))
	{
		Data += line;
	}
	
	return parseFromString(Data);
}


JSON JSON::parseFromString(std::string String)
{
	std::map<std::string, std::string> scenario;
	std::string akt2, akt1 = "";
	while (String.find('"') != std::string::npos) {
		size_t x = String.find('"') + 1;
		while (String[x] != '"') {
			akt1 += String[x];
			x++;
		}
		String.erase(0, x + 1);

		if ((akt1 == "name") || (akt1 == "hero") || (akt1 == "monsters") || (akt1 == "lore") || (akt1 == "race")) {
			size_t x = String.find('"') + 1;
			while (String[x] != '"') {
				akt2 += String[x];
				x++;
			}
			String.erase(0, x + 1);
		}
		else {
			x = 0;
			while (isdigit(String[x]) || (String[x] == '.') || akt2 == "") {
				if ((isdigit(String[x])) || (String[x]=='.')) {
					akt2 += String[x];
				}
				x++;
			}
			String.erase(0, x + 1);
		}

		scenario.insert(std::pair<std::string, std::string>(akt1, akt2));
		akt1 = "";
		akt2 = "";
	}

	return JSON(scenario);
}

bool JSON::count(std::string String)
{
	return scenario.count(String);
}

std::map<std::string, std::string> JSON::getMap()
{
	return scenario;
}

