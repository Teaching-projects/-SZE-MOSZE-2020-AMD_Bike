/**
* \class Map
*
* \brief Map class
*
* This class's role is that it gets a map from a file. In this map the '#' character indicates the wall, and a ' ' indicates the free space, where the Character can move.
*
* \author skrobi12, hajdunorbi, Szabi1104
*
* \version 7.0
*
* \date 2020/11/22 19:17
*/


#ifndef MAP_H
#define MAP_H

#include <string>
#include <fstream>
#include <vector>

class Map{
protected:
	std::vector<std::string> map;		///< This is a vector type variable, which contains the map of the game.

public:
	Map();
	/**
	* \brief This constructor function gets a the map from the given file.
	* \param filename
	* [in] This is the name of the given file, in which the map is located.
	*/
	Map(std::string filename);

	///This is an enum for the map, with which we can give the correct information about the field. 
	enum type
	{
		Free,		///< This is the walkable area.
		Wall		///< This is the blocked area.
	};

	/**
	* \brief This function returns the coordinates type (Free/Walk).
	* \param x
	* \param y
	* \return Returns a Wall enum type, if there is a '#' character, and Free enum type, if there is a ' ' character, where the Character can move.
	*
	*/
	Map::type get(int x, int y) const;

	int GetTheLongestRow();

	int GetMapSize();

	std::string GetRow(int xRow);

	class WrongIndexException : public std::runtime_error {
	public:
		/**
		* \brief This function returns the appropriate error message.
		* \param errMsg
		* \return Returns the appropriate error message.
		*
		*/
		WrongIndexException(const std::string& errMsg) : std::runtime_error(errMsg) {}
	};
};

#endif
