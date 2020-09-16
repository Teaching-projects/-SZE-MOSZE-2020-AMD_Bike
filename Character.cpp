#include "Character.h"

Character::Character(std::string name, int hp, int dmg) : name(name), hp(hp), dmg(dmg)
{
}

std::string Character::getName()
{
	return name;
}

int Character::getHp()
{
	return hp;
}

int Character::getDmg()
{
	return dmg;
}

void Character::Fight(Character character)
{
	int n = 0;
	int char1HP = hp;
	int char2HP = character.getHp();
	std::cout << name << ' ' << hp << ' ' << dmg << std::endl;
	std::cout << character.getName() << ' ' << character.getHp() << ' ' << character.getDmg() << std::endl;
	while (char1HP != 0 && char2HP != 0) {
		std::cout << name << ": HP: " << char1HP << ", DMG: " << dmg << std::endl;
		std::cout << character.getName() << ": HP: " << char2HP << ", DMG: " << character.getDmg() << std::endl;
		if (n % 2 == 0) {
			std::cout << name << "->" << character.getName() << std::endl;
			char2HP -= dmg;
			if (char2HP < 0) { char2HP = 0; }
		}
		else {
			std::cout << character.getName() << "->" << name << std::endl;
			char1HP -= character.getDmg();
			if (char1HP < 0) { char1HP = 0; }
		}
		n++;
	}
	std::cout << name << ": HP: " << char1HP << ", DMG: " << dmg << std::endl;
	std::cout << character.getName() << ": HP: " << char2HP << ", DMG: " << character.getDmg() << std::endl;

	if (char1HP == 0) { std::cout << name << " died. " << character.getName() << " wins." << std::endl; }
	else { std::cout << character.getName() << " died. " << name << " wins." << std::endl; }
}
