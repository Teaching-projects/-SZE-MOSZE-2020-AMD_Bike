#include "Map.h"

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

int Map::GetTheLongestRow() const
{
	int Max = 0;
	for (int i = 0; i < static_cast<int>(map.size()); i++) {
		if (static_cast<int>(map[i].size()) > Max) {
			Max = static_cast<int> (map[i].size());
		}
	}
	return Max;
}

int Map::GetMapSize() const
{
	return static_cast<int> (map.size());
}

std::string Map::GetRow(int xRow) const
{
	return map[xRow];
}

void Map::setMap(int x, int y, char c)
{
	map[y][x] = c;
}
