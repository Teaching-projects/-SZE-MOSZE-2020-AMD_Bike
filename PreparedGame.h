/**
* \class MarkedMap
*
* \brief MarkedMap class
*
* This class's role is that it gets a map from a file. In this map the '#' character indicates the wall, and a ' ' indicates the free space, where the Character can move. <br> Also the 'H' shows where our hero starts on the map and numbers indicate the different monsters' positions.
*
* \author skrobi12, hajdunorbi, Szabi1104
*
* \version 10.0
*
* \date 2020/11/30 16:17
*/


#ifndef PREPAREDGAME_H
#define PREPAREDGAME_H

#include <string>
#include <fstream>
#include <vector>
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
};

#endif