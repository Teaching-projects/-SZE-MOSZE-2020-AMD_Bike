﻿#include "Map.h"
#include "Game.h"
#include <iostream>

Game::Game() : GamesMap(Map()), Monsters(), isTheGameRunning(false)
{
	MyHero.hero = nullptr;
	MyHero.coord.x = -1;
	MyHero.coord.y = -1;
}

Game::Game(std::string mapfilename) : GamesMap(Map(mapfilename)), Monsters(), isTheGameRunning(false)
{
	MyHero.hero = nullptr;
	MyHero.coord.x = -1;
	MyHero.coord.y = -1;
}

void Game::setMap(Map map)
{
	if (isTheGameRunning) { throw GameAlreadyStartedException("The game is already running!"); }
	if ((MyHero.coord.x == -1 && MyHero.coord.y == -1) || Monsters.size() == 0) { GamesMap = map; }
	else { throw AlreadyHasUnitsException("The map has already units on it!"); }
}

void Game::putHero(Hero hero, int x, int y)
{
	if (isTheGameRunning) { throw GameAlreadyStartedException("The game is already running!"); }
	if (GamesMap.GetMapSize() != 0) {
		if (GamesMap.get(x, y) == GamesMap.Wall) {
			throw OccupiedException("There is a Wall, can not place a Hero on it!");
		}
		else if (GamesMap.get(x, y) == GamesMap.Free) {
			if (MyHero.coord.x == -1 && MyHero.coord.y == -1) {
				MyHero.hero = new Hero(hero);
				MyHero.coord.x = x;
				MyHero.coord.y = y;
			}
			else { throw AlreadyHasHeroException("There is already a Hero on the map!"); }
		}
	}
	else { throw std::runtime_error("The map does not exists."); }
}

void Game::putMonster(Monster monster, int x, int y)
{
	if (GamesMap.GetMapSize() != 0) {
		if (GamesMap.get(x, y) == GamesMap.Wall) {
			throw OccupiedException("There is a Wall, can not place a Monster on it.");
		}
		else if (GamesMap.get(x, y) == GamesMap.Free) {
			MonsterCoordinates AktMonster = { monster, {x, y} };
			Monsters.push_back(AktMonster);
		}
		else { throw std::runtime_error("The map does not exists."); }
	}
}

void Game::printMap()
{
	std::cout << "╔";
	for (int i = 0; i < GamesMap.GetTheLongestRow(); i++) {
		std::cout << "══";
	}
	std::cout << "╗" << std::endl;
	for (int y = 0; y < GamesMap.GetMapSize(); y++) {
		std::cout << "║";
		for (int x = 0; x < static_cast<int>(GamesMap.GetRow(y).size()); x++) {
			if (GamesMap.get(x, y) == GamesMap.Wall) { std::cout << "██"; }
			else if (MyHero.coord.x == x && MyHero.coord.y == y) { std::cout << "┣┫"; }
			else if (countMonsters(x, y) >= 1) {
				if (countMonsters(x, y) == 1) { std::cout << "M░"; }
				else { std::cout << "MM"; }
			}
			else { std::cout << "░░"; }
		}
		if (static_cast<int>(GamesMap.GetRow(y).size()) < GamesMap.GetTheLongestRow()) {
			for (int i = static_cast<int>(GamesMap.GetRow(y).size()); i < GamesMap.GetTheLongestRow(); i++) {
				std::cout << "██";
			}
		}
		std::cout << "║" << std::endl;
	}
	std::cout << "╚";
	for (int i = 0; i < GamesMap.GetTheLongestRow(); i++) {
		std::cout << "══";
	}
	std::cout << "╝" << std::endl;
}

void Game::printMapOnRun()
{
	int diff1, diff2, diff3, diff4;
	std::cout << "╔";
	diff1 = ((MyHero.coord.x - MyHero.hero->getLightRadius()) > 0 ? (MyHero.coord.x - MyHero.hero->getLightRadius()) : 0);
	diff2 = ((MyHero.coord.x + MyHero.hero->getLightRadius()) < GamesMap.GetTheLongestRow()-1 ? (MyHero.coord.x + MyHero.hero->getLightRadius()) : GamesMap.GetTheLongestRow()-1);
	diff3 = ((MyHero.coord.y - MyHero.hero->getLightRadius()) > 0 ? (MyHero.coord.y - MyHero.hero->getLightRadius()) : 0);
	diff4 = ((MyHero.coord.y + MyHero.hero->getLightRadius()) < GamesMap.GetMapSize()-1 ? (MyHero.coord.y + MyHero.hero->getLightRadius()) : GamesMap.GetMapSize()-1);
	for (int i = diff1; i <= diff2; i++) {
		std::cout << "══";
	}
	std::cout << "╗" << std::endl;
	for (int y = diff3; y <= diff4; y++) {
		std::cout << "║";
		for (int x = diff1; x <= diff2; x++) {
			if (x < static_cast<int>(GamesMap.GetRow(y).size())) {
				if (MyHero.coord.x == x && MyHero.coord.y == y) { std::cout << "┣┫"; }
				else if (countMonsters(x, y) >= 1) {
					if (countMonsters(x, y) == 1) { std::cout << "M░"; }
					else { std::cout << "MM"; }
				}
				else if (GamesMap.get(x, y) == GamesMap.Free) { std::cout << "░░"; }
				else { std::cout << "██"; }
			}
			else { std::cout << "██"; }
		}
		std::cout << "║" << std::endl;
	}
	std::cout << "╚";
	for (int i = diff1; i <= diff2; i++) {
		std::cout << "══";
	}
	std::cout << "╝" << std::endl;
}

int Game::countMonsters(int x, int y)
{
	int count = 0;
	for (auto& i : Monsters) {
		if (i.coord.x == x && i.coord.y == y) {
			count++;
		}
	}
	return count;
}

void Game::moveHero(std::string direction)
{
	if (direction == "north") {
		if (GamesMap.get(MyHero.coord.x, MyHero.coord.y - 1) != GamesMap.Wall) { MyHero.coord.y--; }
		else { std::cout << "Unfortunatelly, you can not move there!" << std::endl; }
	}
	else if (direction == "south") {
		if (GamesMap.get(MyHero.coord.x, MyHero.coord.y + 1) != GamesMap.Wall) { MyHero.coord.y++; }
		else { std::cout << "Unfortunatelly, you can not move there!" << std::endl; }
	}
	else if (direction == "west") {
		if (GamesMap.get(MyHero.coord.x - 1, MyHero.coord.y) != GamesMap.Wall) { MyHero.coord.x--; }
		else { std::cout << "Unfortunatelly, you can not move there!" << std::endl; }
	}
	else if (direction == "east") {
		if (GamesMap.get(MyHero.coord.x + 1, MyHero.coord.y) != GamesMap.Wall) { MyHero.coord.x++; }
		else { std::cout << "Unfortunatelly, you can not move there!" << std::endl; }
	}
	else { std::cout << "The only acceptable commands are: north/south/west/east" << std::endl; }
}

void Game::isThereAMonster()
{
	std::list<MonsterCoordinates>::iterator OneMonster = Monsters.begin();
	while (OneMonster != Monsters.end()) {
		if (MyHero.coord.x == OneMonster->coord.x && MyHero.coord.y == OneMonster->coord.y) {
			std::cout << MyHero.hero->getName() << " vs " << OneMonster->monster.getName() << std::endl;
			MyHero.hero->fightTilDeath(OneMonster->monster);
			if (!MyHero.hero->isAlive()) {
				std::cout << std::endl << "The hero died." << std::endl;
				isTheGameRunning = false;
				MyHero.coord.x = -1;
				MyHero.coord.y = -1;
				break;
			}
		}
		if (!OneMonster->monster.isAlive())OneMonster = Monsters.erase(OneMonster);
		else OneMonster++;
	}
}

void Game::run()
{
	if (GamesMap.GetMapSize() == 0 || (MyHero.coord.x == -1 && MyHero.coord.y == -1)) { throw NotInitializedException("The map is not set or there is no Hero on the map!"); }
	bool IsNewGame = true;
	isTheGameRunning = true;
	std::string command = "";
	while (isTheGameRunning) {
		printMapOnRun();
		if (IsNewGame) {
			isThereAMonster();
			IsNewGame = false;
		}
		if (MyHero.hero->isAlive()) {
			std::cout << std::endl << "Type north/south/west/east to move your hero in that direction!\n";
			std::cin >> command;
			moveHero(command);
			isThereAMonster();
		}
		std::cout << std::endl << MyHero.hero->getName() << ": LVL" << MyHero.hero->getLevel() << std::endl
			<< "   HP: " << MyHero.hero->getHealthPoints() << "/" << MyHero.hero->getMaxHealthPoints() << std::endl
			<< "  DMG: " << MyHero.hero->getDamage() << std::endl
			<< "  ACD: " << MyHero.hero->getAttackCoolDown() << std::endl;
		if (Monsters.empty()) {
			printMapOnRun();
			std::cout << std::endl << MyHero.hero->getName() << " cleared the map." << std::endl;
			isTheGameRunning = false;
		}
	}
}
