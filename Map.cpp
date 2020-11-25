#include "Map.h"


Map::Map(std::string filename)
{
	std::ifstream file;
	file.open(filename);
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
	if (x > static_cast<int>(map.size())) {
		std::string errMsg = "Wrong 'x' coordinate was given!";
		throw WrongIndexException(errMsg);
	}
	if (y > static_cast<int>(map[x].size())) {
		std::string errMsg = "Wrong 'y' coordinate was given!";
		throw WrongIndexException(errMsg);
	}
	if (map[x][y] == '#') return Map::type::Wall;
	else return Map::type::Free;
}