#include<iostream>
#include "Character.h"
#include<fstream>

void Fight(Character character1, Character character2) {
	int n = 0;
	while (character1.getHp() != 0 && character2.getHp() != 0) {
		if (n % 2 == 0) {
			character2.DMGTaken(character1);
		}
		else {
			character1.DMGTaken(character2);
		}
		n++;
	}

	if (character1.IsDead()) { std::cout << character2.getName() << " wins. Remaining HP: " << character2.getHp() << std::endl; }
	else { std::cout << character1.getName() << " wins. Remaining HP: " << character1.getHp() << std::endl; }
}

int main(int argc, char* argv[]) {

	if (argc < 3) {
		std::cout << "Not enough arguments." << std::endl;
		return 1;
	}
	else if (argc > 3) {
		std::cout << "Too many arguments." << std::endl;
		return 1;
	}
	else {
		try
		{
			Fight(Character::parseUnit(argv[1]), Character::parseUnit(argv[2]));
		}
		catch (const int& e)
		{
			std::cout << "One of the given arguments does not exists."<< std::endl;
			return e;
		}
	}
	return 0;
}