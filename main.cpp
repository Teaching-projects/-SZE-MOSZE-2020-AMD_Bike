#include<iostream>
#include "Character.h"

int main() {
	/*Lefutás konstans karakterek mellett
	Character Maple("Maple", 150, 10);
	Character Sally("Sally", 45, 30);

	Maple.Fight(Sally);*/

	std::cout << "Character name: " << std::endl;
	std::string name;
	std::cin >> name;
	std::cout << "Character HP: " << std::endl;
	int HP;
	std::cin >> HP;
	std::cout << "Character DMG: " << std::endl;
	int DMG;
	std::cin >> DMG;
	Character C1(name, HP, DMG);
	std::cout << "Enemy name: " << std::endl;
	std::cin >> name;
	std::cout << "Enemy HP: " << std::endl;
	std::cin >> HP;
	std::cout << "Enemy DMG: " << std::endl;
	std::cin >> DMG;
	Character C2(name, HP, DMG);
	C1.Fight(C2);

	return 0;
}