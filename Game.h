/**
* \class Game
*
* \brief Game class
*
* This class 
*
* \author skrobi12, hajdunorbi, Szabi1104
*
* \version 8.0
*
* \date 2020/11/22 19:17
*/


#ifndef GAME_H
#define GAME_H

#include <string>
#include <iostream>
#include <fstream>
#include <list>
#include "Map.h"
#include "Monster.h"
#include "Hero.h"

struct HeroCoordinates {
	Hero* hero;
	int x;
	int y;
	~HeroCoordinates() { delete hero; }
};

struct MonsterCoordinates {
	Monster monster;
	int x;
	int y;
};

class Game {
public:
	Map GamesMap;
	HeroCoordinates MyHero;
	std::list<MonsterCoordinates> Monsters;
	bool isTheGameRunning;
//public:
	Game();
	Game(std::string mapfilename);
	void setMap(Map map);
	void putHero(Hero hero, int x, int y);
	void putMonster(Monster monster, int x, int y);
	void printMap();
	int countMonsters(int x, int y);
	void run();
	void moveHero(std::string direction);
	void isThereAMonster();

	class OccupiedException : public std::runtime_error {
	public:
		/**
		* \brief This function returns the appropriate error message.
		* \param errMsg
		* \return Returns the appropriate error message.
		*
		*/
		OccupiedException(const std::string& errMsg) : std::runtime_error(errMsg) {}
	};

	class AlreadyHasHeroException : public std::runtime_error {
	public:
		/**
		* \brief This function returns the appropriate error message.
		* \param errMsg
		* \return Returns the appropriate error message.
		*
		*/
		AlreadyHasHeroException(const std::string& errMsg) : std::runtime_error(errMsg) {}
	};

	class AlreadyHasUnitsException : public std::runtime_error {
	public:
		/**
		* \brief This function returns the appropriate error message.
		* \param errMsg
		* \return Returns the appropriate error message.
		*
		*/
		AlreadyHasUnitsException(const std::string& errMsg) : std::runtime_error(errMsg) {}
	};

	class NotInitializedException : public std::runtime_error {
	public:
		/**
		* \brief This function returns the appropriate error message.
		* \param errMsg
		* \return Returns the appropriate error message.
		*
		*/
		NotInitializedException(const std::string& errMsg) : std::runtime_error(errMsg) {}
	};

	class GameAlreadyStartedException : public std::runtime_error {
	public:
		/**
		* \brief This function returns the appropriate error message.
		* \param errMsg
		* \return Returns the appropriate error message.
		*
		*/
		GameAlreadyStartedException(const std::string& errMsg) : std::runtime_error(errMsg) {}
	};
};

#endif
