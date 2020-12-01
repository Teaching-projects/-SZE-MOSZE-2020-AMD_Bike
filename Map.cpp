#include "Map.h"
#include <iostream>

Map::Map() : map() {

}

Map::Map(std::string filename)
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

Map::type Map::get(int x, int y) const
{
	if (y > static_cast<int>(map.size())) {
		std::string errMsg = "Wrong 'y' coordinate was given!";
		throw WrongIndexException(errMsg);
	}
	if (x > static_cast<int>(map[y].size())) {
		std::string errMsg = "Wrong 'x' coordinate was given!";
		throw WrongIndexException(errMsg);
	}
	if (map[y][x] == '#') return Map::type::Wall;
	else return Map::type::Free;
}

int Map::GetTheLongestRow()
{
	int Max = 0;
	for (int i = 0; i < static_cast<int>(map.size()); i++) {
		if (static_cast<int>(map[i].size()) > Max) {
			Max = static_cast<int> (map[i].size());
		}
	}
	return Max;
}

int Map::GetMapSize()
{
	return static_cast<int> (map.size());
}

std::string Map::GetRow(int xRow)
{
	return map[xRow];
}

MarkedMap::MarkedMap(std::string filename)
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
