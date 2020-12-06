/**
* \class PreparedGame
*
* \brief PreparedGame class
*
*  This class's role is to set a prepared game from an existing json file. 
*
* \author skrobi12, hajdunorbi, Szabi1104
*
* \version 11.0
*
* \date 2020/12/02 14:17
*/


#ifndef PREPAREDGAME_H
#define PREPAREDGAME_H

#include "Game.h"

class PreparedGame : protected Game {
public:
	/**
	* \brief This constructor function initializes the PreparedGame, with the given data in the parameter.
	* \param prepgamename
	* [in] It contains the name of the given map, hero and monsters files.
	*/
	PreparedGame(std::string prepgamename);
	using Game::run;
	using Game::registerRenderer;
	using Game::getTextures;
};

#endif
