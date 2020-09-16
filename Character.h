#ifndef CHARACTER_H
#define CHARACTER_H

#include <string>
#include <iostream>

class Character {
private:
	const std::string name;
	const int hp;
	const int dmg;
public:
	Character(std::string name, int hp, int dmg);
	std::string getName();
	int getHp();
	int getDmg();
	void Fight(Character character);
};

#endif