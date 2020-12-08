#include <iostream>
#include <string>
#include <sstream>
#include <filesystem>
#include <algorithm>
#include <iterator>
#include <map>
#include <list>
#include <vector>

#include "Monster.h"
#include "PreparedGame.h"
#include "TextRenderer.h"
#include "SVGRenderer.h"


const std::map<int, std::string> error_messages = {
	{ 1 , "Bad number of arguments. Only a single scenario file should be provided." },
	{ 2 , "The provided scenario file is not accessible." },
	{ 3 , "The provided scenario file is invalid." },
	{ 4 , "JSON parsing error." },
	{ 5 , "The given command is inappropiate." }
};

void bad_exit(int exitcode) {
	std::cerr
		<< (error_messages.count(exitcode) ? error_messages.at(exitcode) : "Unknown error")
		<< std::endl;
	exit(exitcode);
}




Coordinates coutcord()
{
	Coordinates coord;
	std::cout << "Give the x, y coordinates of the hero! (The upper left corner is 1, 1.)" << std::endl;
	std::cout << "X: " << std::endl;
	std::cin >> coord.x;
	std::cout << "Y: " << std::endl;
	std::cin >> coord.y;
	return coord;
}

int main(int argc, char** argv) {

	if (argc == 1) {
		std::string difficulty;
		std::string command;
		std::cout << "Welcome to the game!" << std::endl;
		while(((command == "1") || (command == "2")) && ((difficulty == "1") || (difficulty == "2")))
		std::cout << "Choose one of the game difficulties below, using their numbers:" << std::endl;
		std::cout << "1 - Normal, where you can see the entire map" << std::endl;
		std::cout << "2 - Hard, where your sight is limited to your Hero's vision" << std::endl;
		std::cin >> difficulty;
		std::cout << "Choose one of the game modes below, using their numbers:" << std::endl;
		std::cout << "1 - Prepared game" << std::endl;
		std::cout << "2 - Set your own game" << std::endl;
		std::cin >> command;

		if (command == "1") {
			PreparedGame Game("preparedgame2.json");
			if (difficulty == "1") {
				Game.registerRenderer(new ObserverTextRenderer());
				Game.registerRenderer(new ObserverSVGRenderer("ObserverOutput.svg"));
				Game.run();
			}
			else if (difficulty == "2") {
				Game.registerRenderer(new HeroTextRenderer());
				Game.registerRenderer(new CharacterSVGRenderer("CharacterOutput.svg"));
				Game.run();
			}
		}
		else if (command == "2") {
			Game TheGame;
			TheGame.registerRenderer(new ObserverTextRenderer());
			std::map<std::string, Hero> HeroMap;
			std::map<std::string, Monster> MonsterMap;
			std::vector<std::string> MapList;

			JSON Units = JSON::parseFromFile("test/units/units.json");
			if (!(Units.count("heroes") && Units.count("monsters"))) bad_exit(3);
			else {
				JSON::list heroes_file_list = Units.get<JSON::list>("heroes");
				for (auto hero_file : heroes_file_list) {
					Hero AktHero = Hero::parse(std::get<std::string>(hero_file));
					HeroMap.insert({ AktHero.getName(), AktHero });
				}
				JSON::list monsters_file_list = Units.get<JSON::list>("monsters");

				for (auto monster_file : monsters_file_list) {
					Monster AktMonster = Monster::parse(std::get<std::string>(monster_file));
					MonsterMap.insert({ AktMonster.getName(), AktMonster });
				}
			}
			JSON Maps = JSON::parseFromFile("test/maps/maps.json");
			if (!(Maps.count("maps"))) bad_exit(3);
			else {
				JSON::list maps_file_list = Maps.get<JSON::list>("maps");
				for (auto map_file : maps_file_list) {
					MapList.push_back(std::get<std::string>(map_file));
				}
			}
			while (command != "exit") {
				std::cout << std::endl << "Choose one of the commands below, using their numbers (or exit to exit):" << std::endl;
				std::cout << "1 - set maps\n2 - put heroes\n3 - put monsters\n4 - run\nexit - exit\n" << std::endl;
				std::cin >> command;
				if (command == "1") {
					std::cout << std::endl << "Choose a map, using their numbers (or back to go back):" << std::endl;
					for (int i = 0; i < static_cast<int>(MapList.size()); i++) {
						std::cout << i + 1 << " - " << MapList[i] << std::endl;
					}
					std::cout << "back - back" << std::endl;
					std::cin >> command;
					if ((command.empty() || !(std::all_of(command.begin(), command.end(), [](char c) {return std::isdigit(c); }))) && command != "back")
						bad_exit(5);
					else if (command != "back") {
						if (stoi(command) > static_cast<int>(MapList.size()) || stoi(command) < 0) { bad_exit(5); }
						TheGame.setMap(MapList[stoi(command) - 1]);
						std::cout << "The chosen map is: " << std::endl;
						TheGame.printBeforeRun();
					}
				}
				else if (command == "2") {
					std::cout << std::endl << "Choose a hero, which you want to put on the map, using their numbers (or back to go back):" << std::endl;
					int i = 1;
					for (auto &AktHero : HeroMap) {
						std::cout << i << " - " << AktHero.first << std::endl;
						i++;
					}
					std::cout << "back - back" << std::endl;
					std::cin >> command;
					if ((command.empty() || !(std::all_of(command.begin(), command.end(), [](char c) {return std::isdigit(c); }))) && command != "back")
						bad_exit(5);
					else if (command != "back") {
						if (stoi(command) >= i || stoi(command) < 0) { bad_exit(5); }
						Coordinates coord = coutcord();
						i = 1;
						for (auto &AktHero : HeroMap) {
							std::cout << AktHero.second.getName() << std::endl;
							if (i == stoi(command)) TheGame.putHero(AktHero.second, coord.y, coord.x);
							i++;
						}
						TheGame.printBeforeRun();
					}
				}
				else if (command == "3") {
					std::cout << std::endl << "Choose a monster, which you want to put on the map, using their numbers (or back to go back):" << std::endl;
					int i = 1;
					for (auto &AktMonster : MonsterMap) {
						std::cout << i << " - " << AktMonster.first << std::endl;
						i++;
					}
					std::cout << "back - back" << std::endl;
					std::cin >> command;
					if ((command.empty() || !(std::all_of(command.begin(), command.end(), [](char c) {return std::isdigit(c); }))) && command != "back")
						bad_exit(5);
					else if (command != "back") {
						if (stoi(command) >= i || stoi(command) < 0) { bad_exit(5); }
						Coordinates coord = coutcord();
						i = 1;
						for (auto &AktMonster : MonsterMap) {
							if (i == stoi(command)) TheGame.putMonster(AktMonster.second, coord.y, coord.x);
							i++;
						}
					}
					TheGame.printBeforeRun();
				}
				else if (command == "4") {
					if (difficulty == "2") {
						TheGame.removeRenderer();
						TheGame.registerRenderer(new HeroTextRenderer());
						TheGame.registerRenderer(new CharacterSVGRenderer("CharacterOutput.svg"));
					}
					else TheGame.registerRenderer(new CharacterSVGRenderer("ObserverOutput.svg"));
					TheGame.run();
				}
			}
		}
	}
	else if (argc == 2) {

		if (!std::filesystem::exists(argv[1])) bad_exit(2);
		std::string hero_file;
		std::list<std::string> monster_files;
		try {
			JSON scenario = JSON::parseFromFile(argv[1]);
			if (!(scenario.count("hero") && scenario.count("monsters"))) bad_exit(3);
			else {
				hero_file = scenario.get<std::string>("hero");
				JSON::list monster_file_list = scenario.get<JSON::list>("monsters");
				for (auto monster_file : monster_file_list)
					monster_files.push_back(std::get<std::string>(monster_file));
			}
		}
		catch (const JSON::ParseException& e) { bad_exit(4); }
		try {
			Hero hero{ Hero::parse(hero_file) };
			std::list<Monster> monsters;
			for (const auto& monster_file : monster_files)
				monsters.push_back(Monster::parse(monster_file));

			while (hero.isAlive() && !monsters.empty()) {
				std::cout
					<< hero.getName() << "(" << hero.getLevel() << ")"
					<< " vs "
					<< monsters.front().getName()
					<< std::endl;
				hero.fightTilDeath(monsters.front());
				if (!monsters.front().isAlive()) monsters.pop_front();
			}
			std::cout << (hero.isAlive() ? "The hero won." : "The hero died.") << std::endl;
			std::cout << hero.getName() << ": LVL" << hero.getLevel() << std::endl
				<< "   HP: " << hero.getHealthPoints() << "/" << hero.getMaxHealthPoints() << std::endl
				<< "  DMG: " << hero.getDamage() << std::endl
				<< "  ACD: " << hero.getAttackCoolDown() << std::endl
				;
		}
		catch (const JSON::ParseException& e) { bad_exit(4); }
	}
	else { bad_exit(1); }
	return 0;
}
