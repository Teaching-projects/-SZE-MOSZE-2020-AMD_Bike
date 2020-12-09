#include "Game.h"
#include <iostream>

Game::Game() : GamesMap(Map()), Monsters(), isTheGameRunning(false)
{
	MyHero.hero = nullptr;
	MyHero.coord.x = -1;
	MyHero.coord.y = -1;
	Textures["WallTexture"] = std::string("test/textures/Wall.jpg");
	Textures["FreeTexture"] = std::string("test/textures/Free.jpg");
}

Game::Game(const std::string &mapfilename) : GamesMap(Map(mapfilename)), Monsters(), isTheGameRunning(false)
{
	MyHero.hero = nullptr;
	MyHero.coord.x = -1;
	MyHero.coord.y = -1;
	Textures["WallTexture"] = std::string("test/textures/Wall.jpg");
	Textures["FreeTexture"] = std::string("test/textures/Free.jpg");
}

Map Game::getMap() const 
{ 
	return GamesMap;
}

char Game::getMapValue(int x, int y) const 
{
	return GamesMap.GetRow(x)[y];
}

HeroCoordinates Game::getHero() const 
{ 
	return MyHero;
}

std::map<std::string, std::string> Game::getTextures() const
{
	return Textures;
}

bool Game::isMonsterAlive(int x, int y) const
{
	for (auto& i : Monsters) {
		if (i.coord.x == x && i.coord.y == y && i.monster.isAlive()) {
			return true;
		}
	}
	return false;
}

void Game::setMap(const Map &map)
{
	if (isTheGameRunning) { throw GameAlreadyStartedException("The game is already running!"); }
	if ((MyHero.coord.x == -1 && MyHero.coord.y == -1) && Monsters.size() == 0) { GamesMap = map; }
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
				GamesMap.setMap(x, y, 'H');
				Textures["HeroTexture"] = std::string("test/textures/") += hero.getTexture();
			}
			else { throw AlreadyHasHeroException("There is already a Hero on the map!"); }
		}
	}
	else { throw std::runtime_error("The map does not exists."); }
}

void Game::moveHero(const std::string &direction)
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
	else { std::cout << "The only acceptable commands are: north/south/west/east (or ff if you want to surrender)" << std::endl; }
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
			char c;
			for (int i = 0; i <= static_cast<int>(monster.getTexture().size()); i++) { if (isdigit(monster.getTexture()[i])) c = monster.getTexture()[i]; }
			GamesMap.setMap(x, y, c);
			if (!Textures.count(Textures[std::string("MonsterTexture-") += c])) Textures[std::string("MonsterTexture-") += c] = (std::string("test/textures/Monster") += c) += std::string(".jpg");
		}
		else { throw std::runtime_error("The map does not exists."); }
	}
}

int Game::countMonsters(int x, int y) const
{
	int count = 0;
	for (auto& i : Monsters) {
		if (i.coord.x == x && i.coord.y == y) {
			count++;
		}
	}
	return count;
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
				print();
				break;
			}
		}
		if (!OneMonster->monster.isAlive())OneMonster = Monsters.erase(OneMonster);
		else ++OneMonster;
	}
}

void Game::registerRenderer(Renderer* renderer)
{
	renderers.push_back(renderer);
}

void Game::removeRenderer()
{
	renderers.pop_front();
}

void Game::print() {
	for (auto &renderer : renderers)
		renderer->render(*this);
}

void Game::run()
{
	if (GamesMap.GetMapSize() == 0 || (MyHero.coord.x == -1 && MyHero.coord.y == -1)) { throw NotInitializedException("The map is not set or there is no Hero on the map!"); }
	bool IsNewGame = true;
	isTheGameRunning = true;
	std::string command = "";
	while (isTheGameRunning) {
		print();
		if (IsNewGame) {
			isThereAMonster();
			IsNewGame = false;
		}
		if (MyHero.hero->isAlive()) {
			std::cout << std::endl << "Type north/south/west/east to move your hero in that direction! (or type ff to surrender)\n";
			std::cin >> command;
			if (command != "ff") moveHero(command);
			else { 
				std::cout << "Your hero retreated, you lost the game." << std::endl;
				break;
			}
			
			isThereAMonster();
		}
		std::cout << std::endl << MyHero.hero->getName() << ": LVL" << MyHero.hero->getLevel() << std::endl
			<< "   HP: " << MyHero.hero->getHealthPoints() << "/" << MyHero.hero->getMaxHealthPoints() << std::endl
			<< "  DMG: " << MyHero.hero->getDamage() << std::endl
			<< "  ACD: " << MyHero.hero->getAttackCoolDown() << std::endl;
		if (Monsters.empty()) {
			print();
			std::cout << std::endl << MyHero.hero->getName() << " cleared the map." << std::endl;
			isTheGameRunning = false;
		}
	}
}
