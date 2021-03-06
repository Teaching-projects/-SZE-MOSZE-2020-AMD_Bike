/**
* \class JSON
*
* \brief JSON class
*
* This class's role is, to prepare the Hero and Monster class's parse function for 3 types of input. These input's are the istream, filename and string.
*
* \author skrobi12, hajdunorbi, Szabi1104
*
* \version 4.0
*
* \date 2020/11/04 19:17
*/


#ifndef JSON_H
#define JSON_H

#include <map>
#include <string>
#include <fstream>
#include <variant>
#include <algorithm> 
#include <list> 
#include <iterator> 

using VariantMap = std::map <std::string, std::variant<std::string, int, double>>;

class JSON {
private:
	VariantMap data;				///< This is a map type variable, which contains the Hero and all the Monsters, that the Hero will fight against.

public:
	/**
	* \brief This constructor function initializes the data.
	* \param data
	* [in] This is a map type variable, which contains the Hero and all the Monsters, that the Hero will fight against.
	*/
	explicit JSON(const VariantMap& data);

	/**
	* \brief This function opens the given input (in the current case a FileName). After a FileName is given, this function makes a string from it, and calls the ParserFromString() function, whit the created string as parameter.
	* \param FileName
	* \return Returns a <string, string> type map, which contains all the necessary data, what a Hero or Monster has.
	*
	*/
	static JSON parseFromFile(std::string FileName);

	/**
	* \brief This function opens the given input (in the current case an Istream). After an Istream is given, this function makes a string from it, and calls the ParserFromString() function, whit the created string as parameter.
	* \param Istream
	* \return Returns a <string, string> type map, which contains all the necessary data, what a Hero or Monster has.
	*
	*/
	static JSON parseFromFile(std::istream& Istream);

	/**
	* \brief This function gets a String as an argument, or from the listed functions before. Then the function loads the parameters, which it gets from the String, into a Map, and returns this Map.
	* \param String
	* \return Returns a <string, string> type map, which contains all the necessary data, what a Hero or Monster has.
	*
	*/
	static JSON parseFromString(std::string String);

	/**
	* \brief This function checks if there is a monster or a hero, in the actual scenario file.
	* \param String
	* \return Returns true if there is a Hero and Monster(s) in the actual scenario, and false if there is not.
	*
	*/
	bool count(std::string String) const;

	typedef std::list<std::variant<std::string, int, double>> list;

	template <typename T>
	inline typename std::enable_if<std::is_same<T, JSON::list>::value, T>::type
		get(const std::string& type) {
			list toReturn;
			std::istringstream objects(std::get<std::string>(data[type]));
			std::copy(std::istream_iterator<std::string>(objects),
				std::istream_iterator<std::string>(),
				std::back_inserter(toReturn));
			return toReturn;
	}

	template <typename T> inline typename std::enable_if<!std::is_same<T, JSON::list>::value, T>::type 
		get(const std::string& type) {
		return std::get<T>(data[type]);
	}

	class ParseException : public std::runtime_error {
	public:
		/**
		* \brief This function returns the appropriate error message.
		* \param errMsg
		* \return Returns the appropriate error message.
		*
		*/
		explicit ParseException(const std::string& errMsg) : std::runtime_error(errMsg) {}
	};
};

#endif
