#include<iostream>
#include "Character.h"

void Fight(Character character1, Character character2) {
	int n = 0;
	int char1HP = character1.getHp();
	int char2HP = character2.getHp();
	std::cout << character1.getName() << ' ' << character1.getHp() << ' ' << character1.getDmg() << std::endl;
	std::cout << character2.getName() << ' ' << character2.getHp() << ' ' << character2.getDmg() << std::endl;
	while (char1HP != 0 && char2HP != 0) {
		std::cout << character1.getName() << ": HP: " << char1HP << ", DMG: " << character1.getDmg() << std::endl;
		std::cout << character2.getName() << ": HP: " << char2HP << ", DMG: " << character2.getDmg() << std::endl;
		if (n % 2 == 0) {
			std::cout << character1.getName() << "->" << character2.getName() << std::endl;
			char2HP -= character1.getDmg();
			if (char2HP < 0) { char2HP = 0; }
		}
		else {
			std::cout << character2.getName() << "->" << character1.getName() << std::endl;
			char1HP -= character2.getDmg();
			if (char1HP < 0) { char1HP = 0; }
		}
		n++;
	}
	std::cout << character1.getName() << ": HP: " << char1HP << ", DMG: " << character1.getDmg() << std::endl;
	std::cout << character2.getName() << ": HP: " << char2HP << ", DMG: " << character2.getDmg() << std::endl;

	if (char1HP == 0) { std::cout << character1.getName() << " died. " << character2.getName() << " wins." << std::endl; }
	else { std::cout << character2.getName() << " died. " << character1.getName() << " wins." << std::endl; }
}

int main() {
	std::string name;
	int HP;
	int DMG;
	std::cout << "Character name: " << std::endl;
	std::cin >> name;
	std::cout << "Character HP: " << std::endl;
	std::cin >> HP;
	std::cout << "Character DMG: " << std::endl;
	std::cin >> DMG;
	Character C1(name, HP, DMG);
	std::cout << "Enemy name: " << std::endl;
	std::cin >> name;
	std::cout << "Enemy HP: " << std::endl;
	std::cin >> HP;
	std::cout << "Enemy DMG: " << std::endl;
	std::cin >> DMG;
	Character C2(name, HP, DMG);
	Fight(C1, C2); 

	return 0;
}