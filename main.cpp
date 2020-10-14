#include "Character.h"
#include "Player.h"
#include <iostream>

void Fight(Character& fighter1, Character& fighter2) {
	double gameprogress = 0;
	double aktAS1 = fighter1.getAttackspeed();
	double aktAS2 = fighter2.getAttackspeed();

	fighter1.OnePunch(fighter2);
	if (!fighter2.IsDead()) {
		fighter2.OnePunch(fighter1);
	}
	while (!fighter1.IsDead() && !fighter2.IsDead()) {
		if ((aktAS1 - gameprogress) < (aktAS2 - gameprogress)) {
			fighter1.OnePunch(fighter2);
			gameprogress = aktAS1;
			aktAS1 += fighter1.getAttackspeed();
		}
		else if ((aktAS1)-gameprogress > (aktAS2 - gameprogress)) {
			fighter2.OnePunch(fighter1);
			gameprogress = aktAS2;
			aktAS2 += fighter2.getAttackspeed();
		}
		else {
			fighter1.OnePunch(fighter2);
			if (!fighter2.IsDead()) {
				fighter2.OnePunch(fighter1);
			}
			gameprogress = aktAS1;
			aktAS1 += fighter1.getAttackspeed();
			aktAS2 += fighter2.getAttackspeed();
		}
	}
	if (fighter2.IsDead()) {
		std::cout << fighter1.getName() << " wins. Remaining HP: " << fighter1.getHp() << std::endl;
	}
	else {
		std::cout << fighter2.getName() << " wins. Remaining HP: " << fighter2.getHp() << std::endl;
	}
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
	else {
		try
		{
			Player Fighter1 = Player::parsePlayer(argv[1]);
			Character Fighter2 = Character::parseUnit(argv[2]);
			Fight(Fighter1, Fighter2);
		}
		catch (const int& e)
		{
			std::cout << "One of the given arguments does not exists." << std::endl;
			return e;
		}
	}
	return 0;
}
