#ifndef JSON_H
#define JSON_H

#include <map>
#include <string>
#include <fstream>

class JSON {
private:
	std::map<std::string, std::string> scenario;

public:
	JSON(std::map <std::string, std::string> scenario);

	static JSON parseFromFile(std::string FileName);
	static JSON parseFromFile(std::istream Istream);
	static JSON parseFromString(std::string String);
	bool count(std::string String);
	std::map <std::string, std::string> getMap();

	template <class T> T get(const std::string& type) {
		return scenario[type];
	}

	class ParseException : public std::runtime_error {
	public:
		ParseException(const std::string& errMsg) : std::runtime_error(errMsg) {}
	};
};



#endif
