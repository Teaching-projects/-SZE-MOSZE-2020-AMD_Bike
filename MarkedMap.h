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


#ifndef MARKEDMAP_H
#define MARKEDMAP_H

#include "Map.h"
#include "Game.h"

class MarkedMap : public Map {
public:

	/**
	* \brief This function search for the 'H' on the given map, so for the Hero.
	* \return Returns the x and y coordinates of the Hero.
	*
	*/
	Coordinates getHeroPosition() const;

	/**
	* \brief This function search for the diggerent kind of monsters on the map.
	* \param c
	* \return Returns the x and y coordinates of the monsters in a list.
	*
	*/
	std::list<Coordinates> getMonsterPositions(char c) const;
};

#endif
