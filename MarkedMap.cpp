#include "MarkedMap.h"

Coordinates MarkedMap::getHeroPosition() const
{
	for (int y = 0; y < static_cast<int> (map.size()); y++) {
		for (int x = 0; x < static_cast<int>(map[y].size()); x++) {
			if (map[y][x] == 'H') return { x, y };
		}
	}
	throw std::runtime_error("There was no hero given in the map file.");
}

std::list<Coordinates> MarkedMap::getMonsterPositions(char c) const
{
	std::list<Coordinates> MonsterCoordList;
	for (int y = 0; y < static_cast<int> (map.size()); y++) {
		for (int x = 0; x < static_cast<int>(map[y].size()); x++) {
			if (map[y][x] == c) MonsterCoordList.push_back({ x, y });
		}
	}
	return MonsterCoordList;
}
