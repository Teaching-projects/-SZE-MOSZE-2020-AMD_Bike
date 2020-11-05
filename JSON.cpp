#include "JSON.h"
#include <iostream>

JSON::JSON(VariantMap scenario) : scenario(scenario)
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
	VariantMap scenario;
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

		if ((akt1 == "name") || (akt1 == "hero") || (akt1 == "monsters") || (akt1 == "lore") || (akt1 == "race") || (akt1 == "additional_info")) {
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

		if ((akt1 == "name") || (akt1 == "hero") || (akt1 == "monsters") || (akt1 == "lore") || (akt1 == "race") || (akt1 == "additional_info")) scenario[akt1] = akt2;
		else if (akt1 == "base_health_points") scenario[akt1] = std::stoi(akt2);
		else if (akt1 == "base_damage") scenario[akt1] = std::stoi(akt2);
		else if (akt1 == "base_attack_cooldown") scenario[akt1] = std::stod(akt2);
		else if (akt1 == "experience_per_level") scenario[akt1] = std::stoi(akt2);
		else if (akt1 == "health_point_bonus_per_level") scenario[akt1] = std::stoi(akt2);
		else if (akt1 == "damage_bonus_per_level") scenario[akt1] = std::stoi(akt2);
		else if (akt1 == "cooldown_multiplier_per_level") scenario[akt1] = std::stod(akt2);
		else if (akt1 == "health_points")scenario[akt1] = std::stoi(akt2);
		else if (akt1 == "damage") scenario[akt1] = std::stoi(akt2);
		else if (akt1 == "attack_cooldown") scenario[akt1] = std::stod(akt2);


		akt1 = "";
		akt2 = "";
	}

	return JSON(scenario);
}

bool JSON::count(std::string String)
{
	return scenario.count(String);
}