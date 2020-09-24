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
	else { std::cout <<  character1.getName() << " wins. Remaining HP: " << character1.getHp() << std::endl; }
}

bool IsExist(const std::string FileName1, const std::string FileName2) {
	std::ifstream file1, file2;
	file1.open(FileName1);
	file2.open(FileName2);
	if (!file1.is_open() || !file2.is_open()) {
		file1.close();
		file2.close();
		return true;
	}
	else { file1.close(); file2.close(); return false; }
}


int main(int argc, char *argv[]) {
	
	if (argc < 3) {
		std::cout << "Not enough arguments" << std::endl;
		return 1;
	}
	else if (argc > 3) {
		std::cout << "Too many arguments" << std::endl;
		return 1;
	}
	else if (IsExist(argv[1], argv[2])) {
		std::cout << "At least one file not exists" << std::endl;
	}
	else {
		Character Character1 = Character::parseUnit(argv[1]);
		Character Character2 = Character::parseUnit(argv[2]);
		Fight(Character1, Character2);
	}

	return 0;
}