#include<iostream>
#include "Character.h"

void Fight(Character character1, Character character2) {
	int n = 0;
	std::cout << character1.getName() << ' ' << character1.getHp() << ' ' << character1.getDmg() << std::endl;
	std::cout << character2.getName() << ' ' << character2.getHp() << ' ' << character2.getDmg() << std::endl;
	while (character1.getHp() != 0 && character2.getHp() != 0) {
		std::cout << character1.getName() << ": HP: " << character1.getHp() << ", DMG: " << character1.getDmg() << std::endl;
		std::cout << character2.getName() << ": HP: " << character2.getHp() << ", DMG: " << character2.getDmg() << std::endl;
		if (n % 2 == 0) {
			std::cout << character1.getName() << "->" << character2.getName() << std::endl;
			character2.DMGTaken(character1.getDmg());
			character2.Dead();
		}
		else {
			std::cout << character2.getName() << "->" << character1.getName() << std::endl;
			character1.DMGTaken(character2.getDmg());
			character1.Dead();
		}
		n++;
	}
	std::cout << character1.getName() << ": HP: " << character1.getHp() << ", DMG: " << character1.getDmg() << std::endl;
	std::cout << character2.getName() << ": HP: " << character2.getHp() << ", DMG: " << character2.getDmg() << std::endl;

	if (character1.getHp() == 0) { std::cout << character1.getName() << " died. " << character2.getName() << " wins." << std::endl; }
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