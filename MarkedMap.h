/**
* \class MarkedMap
*
* \brief MarkedMap class
*
* -----  This class's role is that it gets a map from a file. In this map the '#' character indicates the wall, and a ' ' indicates the free space, where the Character can move.
*
* \author skrobi12, hajdunorbi, Szabi1104
*
* \version 12.0
*
* \date 2020/12/05 19:17
*/


#ifndef MARKEDMAP_H
#define MARKEDMAP_H

#include "Map.h"

class MarkedMap : public Map {
public:
	/**
	* \brief This constructor function initializes the map, with the given data in the parameter.
	* \param filename
	* [in] It contains the name of the given marked map.
	*/
	MarkedMap(std::string filename);

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
