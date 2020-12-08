/**
* \class Game
*
* \brief Game class
*
* This class jobs is to functionize a running game. It does this on the following way: <br> First a window pops up, where you have to choose a map, from the map list, on which your hero will figth. <br> After that you ahve to choose that hero, and put it on the map, for which you have to give 2 coordinates (x, y). <br> And when your hero is ready, choose monsters from a list, and put them on the field the same way, as you did with your hero. <br> The last step is to run the game, and see if you can beat them all.
*
* \author skrobi12, hajdunorbi, Szabi1104
*
* \version 9.0
*
* \date 2020/11/29 19:17
*/


#ifndef GAME_H
#define GAME_H

#include <string>
#include <iostream>
#include <fstream>
#include "Hero.h"
#include "Map.h"

struct HeroCoordinates {
	Hero* hero;		///< This is pointer variable, that points to a Hero type.
	Coordinates coord;			///< This is a coordinate type variable.
	~HeroCoordinates() { delete hero; }		///< This is the destructor for the hero pointer.
};

struct MonsterCoordinates {
	Monster monster;	///< This is Monster type variable.
	Coordinates coord;			///< This is a coordinate type variable.
};

class Game {
protected:
	Map GamesMap;								///< This is a Map type variable.
	HeroCoordinates MyHero;						///< This is a HeroCoordinates type variable.
	std::list<MonsterCoordinates> Monsters;		///< This is a MonsterCoordinates list, where the monsters are stored.
	bool isTheGameRunning;						///< This bool type variable, which is true, if the game runs.
public:
	Game();

	/**
	* \brief This constructor function initializes the Game, with the given data in the parameter.
	* \param mapfilename
	* [in] It contains the given maps name.
	*/
	Game(std::string mapfilename);

	/**
	* \brief This function sets the map for the game.
	* \param map
	*
	*/
	void setMap(Map map);

	/**
	* \brief This function puts the hero on the given coordinates.
	* \param hero
	* \param x
	* \param y
	*
	*/
	void putHero(Hero hero, int x, int y);

	/**
	* \brief This function puts a monster on the given coordinates.
	* \param hero
	* \param x
	* \param y
	*
	*/
	void putMonster(Monster monster, int x, int y);

	/**
	* \brief This function prints the blank map.
	*
	*/
	void printMap();

	/**
	* \brief This function prints the given map.
	*
	*/
	void printMapOnRun();

	/**
	* \brief This function counts the monsters.
	* \param x
	* \param y
	* \return Returns the count of the monsters, which are on the same x, y coordinate.
	*
	*/
	int countMonsters(int x, int y);

	/**
	* \brief This function runs the game.
	*
	*/
	void run();

	/**
	* \brief This function moves the hero on the map, in the given direction (north/east/south/west).
	* \param direction
	*
	*/
	void moveHero(std::string direction);

	/**
	* \brief This function checks if there are monsters in the hero's way, and if yes, then the hero figths with them.
	*
	*/
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
