#include "JSON.h"
#include <iostream>
#include <vector>

JSON::JSON(VariantMap data) : data(data)
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
		
		std::string errMsg = "The file cannot be opened!";
		throw ParseException(errMsg);
	}

	return parseFromString(Data);
}

JSON JSON::parseFromFile(std::istream& Istream)
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
	std::vector<std::string> Check1 = { "name", "hero", "lore", "race", "additional_info", "map", "monster-1", "monster-2", "monster-3" };
	std::vector<std::string> Check2 = { "monsters", "heroes", "maps" };
	
	VariantMap StringData;
	std::string akt2, akt1 = "";
	while (String.find('"') != std::string::npos) {
		size_t x = String.find('"') + 1;
		while (String[x] != '"') {
			akt1 += String[x];
			x++;
		}
		if (akt1 == "") {
			throw std::runtime_error("No key given!");
		}
		String.erase(0, x + 1);

		if (std::find(Check1.begin(), Check1.end(), akt1) != Check1.end()){
			size_t x = String.find('"') + 1;
			while ((String[x] != '"') && (x != String.size())) {
				if (isupper(String[x]) && (String[x - 1] != '-') && (String[x - 1] != '_') && (akt2 != "")) {
					akt2 = akt2 + ' ' + String[x];
				}
				else if (String[x] != ' ') {
					if (String[x] == 'o' && String[x + 1] == 'f') {
						akt2 = akt2 + ' ' + String[x];
					}
					else {
						akt2 += String[x];
					}
				}
				x++;
			}
			String.erase(0, x + 1);
		}
		else if (std::find(Check2.begin(), Check2.end(), akt1) != Check2.end()) {
			size_t x = String.find('[') + 1;
			while ((String[x] != ']') && (x != String.size())) {
				if (String.find('"') != std::string::npos && String.find(']') != std::string::npos) {
					if (String.find('"') < String.find(']')) x = String.find('"') + 1;
					else x = String.find(']');
				}
				else { x = String.size(); }
				while ((String[x] != ']') && (String[x] != '"') && (x != String.size())) {
					if (isupper(String[x]) && (String[x - 1] != '-') && (String[x - 1] != '_') && (akt2 != "")) {
						akt2 = akt2 + ' ' + String[x];
					}
					else if (String[x] != ' ') {
						if (String[x] == 'o' && String[x + 1] == 'f') {
							akt2 = akt2 + ' ' + String[x];
						}
						else {
							akt2 += String[x];
						}
					}
					x++;
				}
				if (String[x] == ']') String.erase(0, x - 1);
				else String.erase(0, x+1);
			}	
		}
		else {
			x = 0;
			while ((x < String.size()) && (String[x] != '"') && (String[x] != ',')) {
				if (isdigit(String[x]) || (String[x] == '.')) {
					akt2 += String[x];
				}
				if (!((String[x] == ':') || (isspace(String[x])) || (isdigit(String[x])) || (String[x] == '}') || (String[x] == '.'))) {
					throw std::runtime_error("Only digit data is acceptable!");
				}
				x++;
			}
			String.erase(0, x + 1);
		}
		if (akt2 == "") {
			throw std::runtime_error("No value given to the \"" + akt1 + "\" key!");
		}

		if (!akt2.empty() && std::all_of(akt2.begin(), akt2.end(), [](char c) {return std::isdigit(c); })) StringData[akt1] = std::stoi(akt2);
		else if (!akt2.empty() && std::all_of(akt2.begin(), akt2.end(), [](char c) {return ((std::isdigit(c) || c == '.') ? true : false); })) StringData[akt1] = std::stod(akt2);
		else StringData[akt1] = akt2;

		akt1 = "";
		akt2 = "";
	}
	
	return JSON(StringData);
}

bool JSON::count(std::string String) const
{
	return data.count(String);
}

int JSON::getMapSize() const
{
	return data.size();
}
