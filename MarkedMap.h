/**
* \class MarkedMap
*
* \brief MarkedMap class
*
*  ----  This class's role is that it gets a map from a file. In this map the '#' character indicates the wall, and a ' ' indicates the free space, where the Character can move.
*
* \author skrobi12, hajdunorbi, Szabi1104
*
* \version 7.0  ----
*
* \date 2020/11/22 19:17 ----
*/


#ifndef MARKEDMAP_H
#define MARKEDMAP_H

#include <string>
#include <fstream>
#include <vector>
#include "Map.h"
#include "Game.h"

class MarkedMap : public Map {
public:
	Coordinates getHeroPosition() const;
	std::list<Coordinates> getMonsterPositions(char c) const;
};

#endif
