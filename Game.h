/**
* \class Game
*
* \brief Game class
*
* This class jobs is to functionize a running game. It does this on the following way: <br> First a window pops up, where you have to choose a map, from the map list, on which your hero will figth. <br> After that you ahve to choose that hero, and put it on the map, for which you have to give 2 coordinates (x, y). <br> And when your hero is ready, choose monsters from a list, and put them on the field the same way, as you did with your hero. <br> The last step is to run the game, and see if you can beat them all.
*
* \author skrobi12, hajdunorbi, Szabi1104
*
* \version 12.0
*
* \date 2020/12/07 19:17
*/


#ifndef GAME_H
#define GAME_H

#include <string>
#include <fstream>
#include <list>
#include <map>
#include "Hero.h"
#include "MarkedMap.h"
#include "Renderer.h"

class Renderer;

struct HeroCoordinates {
	Hero* hero;		///< This is pointer variable, that points to a Hero type.
	Coordinates coord;			///< This is a coordinate type variable.
};

struct MonsterCoordinates {
	Monster monster;	///< This is Monster type variable.
	Coordinates coord;			///< This is a coordinate type variable.
};

class Game {
protected:
	Map GamesMap;									///< This is a Map type variable.
	HeroCoordinates MyHero;							///< This is a HeroCoordinates type variable.
	std::list<MonsterCoordinates> Monsters;			///< This is a MonsterCoordinates list, where the monsters are stored.
	bool isTheGameRunning;							///< This bool type variable, which is true, if the game runs.
	std::map<std::string, std::string> Textures;	///< This is a map for all the Textures.
public:
	std::list<Renderer*> renderers;					///< This is a list for all the Renderers.

	Game();

	/**
	* \brief This constructor function initializes the Game, with the given data in the parameter.
	* \param mapfilename
	* [in] It contains the given maps name.
	*/
	explicit Game(const std::string &mapfilename);

	/**
	* \brief This is a getter function, which returns the map.
	* \param none
	*
	*/
	Map getMap() const;

	/**
	* \brief This is a getter function, which returns the value of the actual coordinate.
	* \param x
	* \param y
	*
	*/
	char getMapValue(int x, int y) const;

	/**
	* \brief This is a getter function, which returns a hero.
	* \param none
	*
	*/
	HeroCoordinates getHero() const;

	/**
	* \brief This is a getter function, which returns the textures.
	* \param none
	*
	*/
	std::map<std::string, std::string> getTextures() const;

	/**
	* \brief This is a getter function, which returns a monster.
	* \param x
	* \param y
	*
	*/
	bool isMonsterAlive(int x, int y) const;

	/**
	* \brief This function sets the map for the game.
	* \param map
	*
	*/
	void setMap(const Map &map);

	/**
	* \brief This function puts the hero on the given coordinates.
	* \param hero
	* \param x
	* \param y
	*
	*/
	void putHero(Hero hero, int x, int y);

	/**
	* \brief This function moves the hero on the map, in the given direction (north/east/south/west).
	* \param direction
	*
	*/
	void moveHero(const std::string &direction);

	/**
	* \brief This function puts a monster on the given coordinates.
	* \param hero
	* \param x
	* \param y
	*
	*/
	void putMonster(Monster monster, int x, int y);

	/**
	* \brief This function counts the monsters.
	* \param x
	* \param y
	* \return Returns the count of the monsters, which are on the same x, y coordinate.
	*
	*/
	int countMonsters(int x, int y) const;

	/**
	* \brief This function checks if there are monsters in the hero's way, and if yes, then the hero figths with them.
	*
	*/
	void isThereAMonster();

	/**
	* \brief This function adds a new rendering method to the game.
	* \param renderer
	*
	*/
	void registerRenderer(Renderer* renderer);

	/**
	* \brief This function removes the first renderer.
	* \param none
	*
	*/
	void removeRenderer();

	/**
	* \brief This function call the renderers print.
	* \param none
	*
	*/
	void print();

	/**
	* \brief This function runs the game.
	* \param none
	*
	*/
	void run();

	class OccupiedException : public std::runtime_error {
	public:
		/**
		* \brief This function returns the appropriate error message.
		* \param errMsg
		* \return Returns the appropriate error message.
		*
		*/
		explicit OccupiedException(const std::string& errMsg) : std::runtime_error(errMsg) {}
	};

	class AlreadyHasHeroException : public std::runtime_error {
	public:
		/**
		* \brief This function returns the appropriate error message.
		* \param errMsg
		* \return Returns the appropriate error message.
		*
		*/
		explicit AlreadyHasHeroException(const std::string& errMsg) : std::runtime_error(errMsg) {}
	};

	class AlreadyHasUnitsException : public std::runtime_error {
	public:
		/**
		* \brief This function returns the appropriate error message.
		* \param errMsg
		* \return Returns the appropriate error message.
		*
		*/
		explicit AlreadyHasUnitsException(const std::string& errMsg) : std::runtime_error(errMsg) {}
	};

	class NotInitializedException : public std::runtime_error {
	public:
		/**
		* \brief This function returns the appropriate error message.
		* \param errMsg
		* \return Returns the appropriate error message.
		*
		*/
		explicit NotInitializedException(const std::string& errMsg) : std::runtime_error(errMsg) {}
	};

	class GameAlreadyStartedException : public std::runtime_error {
	public:
		/**
		* \brief This function returns the appropriate error message.
		* \param errMsg
		* \return Returns the appropriate error message.
		*
		*/
		explicit GameAlreadyStartedException(const std::string& errMsg) : std::runtime_error(errMsg) {}
	};

};

#endif
