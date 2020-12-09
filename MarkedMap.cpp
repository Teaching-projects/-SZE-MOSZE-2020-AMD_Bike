#include "MarkedMap.h"

MarkedMap::MarkedMap(const std::string& filename)
{
	std::ifstream file;
	file.open("test/maps/" + filename);
	std::string line;
	if (file.is_open()) {
		while (getline(file, line)) {
			map.push_back(line);
		}
		file.close();
	}
	else {
		throw std::runtime_error("The file cannot be opened!");
	}

}

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
