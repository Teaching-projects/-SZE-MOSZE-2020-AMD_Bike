#include "Map.h"
#include "Game.h"
#include <iostream>

Game::Game() : GamesMap(Map()), Monsters(), isTheGameRunning(false)
{
	MyHero.hero = nullptr;
	MyHero.x = -1;
	MyHero.y = -1;
}

Game::Game(std::string mapfilename) : GamesMap(Map(mapfilename)), Monsters(), isTheGameRunning(false)
{
	MyHero.hero = nullptr;
	MyHero.x = -1;
	MyHero.y = -1;
}

void Game::setMap(Map map)
{
	if (isTheGameRunning) { throw GameAlreadyStartedException("The game is already running!"); }
	if ((MyHero.x == -1 && MyHero.y == -1) || Monsters.size() == 0) { GamesMap = map; }
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
			if (MyHero.x == -1 && MyHero.y == -1) {
				MyHero.hero = new Hero(hero);
				MyHero.x = x;
				MyHero.y = y;
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
			MonsterCoordinates AktMonster = { monster, x, y };
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
			else if (MyHero.x == x && MyHero.y == y) { std::cout << "┣┫"; }
			else if (countMonsters(x, y) >= 1) {
				if (countMonsters(x, y) == 1) { std::cout << "M░"; }
				else { std::cout << "MM"; }
			}
			else if (GamesMap.get(x, y) == GamesMap.Free) { std::cout << "░░"; }
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

int Game::countMonsters(int x, int y)
{
	int count = 0;
	for (auto &i : Monsters) {
		if (i.x == x && i.y == y) {
			count++;
		}
	}
	return count;
}

void Game::moveHero(std::string direction)
{
	if (direction == "north") {
		if (GamesMap.get(MyHero.x, MyHero.y - 1) != GamesMap.Wall) { MyHero.y--; }
		else { std::cout << "Unfortunatelly, you can not move there!" << std::endl; }
	}
	else if (direction == "south") {
		if (GamesMap.get(MyHero.x, MyHero.y + 1) != GamesMap.Wall) { MyHero.y++; }
		else { std::cout << "Unfortunatelly, you can not move there!" << std::endl; }
	}
	else if (direction == "west") {
		if (GamesMap.get(MyHero.x - 1, MyHero.y) != GamesMap.Wall) { MyHero.x--; }
		else { std::cout << "Unfortunatelly, you can not move there!" << std::endl; }
	}
	else if (direction == "east") {
		if (GamesMap.get(MyHero.x + 1, MyHero.y) != GamesMap.Wall) { MyHero.x++; }
		else { std::cout << "Unfortunatelly, you can not move there!" << std::endl; }
	}
	else { std::cout << "The only acceptable commands are: north/south/west/east" << std::endl; }
}

void Game::isThereAMonster()
{
	std::list<MonsterCoordinates>::iterator OneMonster = Monsters.begin();
	while (OneMonster != Monsters.end()) {
		if (MyHero.x == OneMonster->x && MyHero.y == OneMonster->y) {
			std::cout << MyHero.hero->getName() << " vs " << OneMonster->monster.getName() << std::endl;
			MyHero.hero->fightTilDeath(OneMonster->monster);
			if (!MyHero.hero->isAlive()) {
				std::cout << std::endl << "The hero died." << std::endl;
				isTheGameRunning = false;
				MyHero.x = -1;
				MyHero.y = -1;
				break;
			}
		}
		if(!OneMonster->monster.isAlive())OneMonster = Monsters.erase(OneMonster);
		else OneMonster++;
	}
}

void Game::run()
{
	if (GamesMap.GetMapSize() == 0 || (MyHero.x == -1 && MyHero.y == -1)) { throw NotInitializedException("The map is not set or there is no Hero on the map!"); }
	bool IsNewGame = true;
	isTheGameRunning = true;
	std::string command = "";
	while (isTheGameRunning) {
		printMap();
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
			printMap();
			std::cout << std::endl << MyHero.hero->getName() << " cleared the map." << std::endl;
			isTheGameRunning = false;
		}
	}
}
