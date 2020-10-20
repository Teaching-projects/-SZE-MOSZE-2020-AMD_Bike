#include "Character.h"
#include <iostream>

Character::Character(const std::string name, const int hp, const int dmg, const double attackspeed) : name(name), hp(hp), dmg(dmg), attackspeed(attackspeed)
{
}

std::string Character::getName() const
{
	return name;
}

int Character::getHp() const
{
	return hp;
}

int Character::getDmg() const
{
	return dmg;
}

double Character::getAttackspeed() const
{
	return attackspeed;
}

bool Character::IsDead() const
{
	return hp == 0;
}

Character Character::parseUnit(const std::string& FileName)
{
	std::ifstream file;
	std::string line, name;
	int hp, dmg;
	double attackspeed;
	file.open(FileName);

	if (file.is_open()) {
		int i = 0;
		while (!file.eof()) {
			getline(file, line);
			if (i == 1) {
				size_t x = line.find(':');
				size_t y = line.find(',');
				x += 3;
				y = y - x - 1;
				name = line.substr(x, y);

			}
			else if (i == 2) {
				size_t x = line.find(':');
				size_t y = line.find(',');
				x += 2;
				y = y - x;
				hp = stoi(line.substr(x, y));
			}
			else if (i == 3) {
				size_t x = line.find(':');
				size_t y = line.find(',');
				x += 2;
				y = y - x;
				dmg = stoi(line.substr(x, y));
			}
			else if (i == 4) {
				size_t x = line.find(':');
				attackspeed = stod(line.substr(x + 2));
			}
			i++;
		}
	}
	else {
		throw 1;
	}
	file.close();
	Character character(name, hp, dmg, attackspeed);
	return character;
}

void Character::DMGTaken(Character& foe)
{
	hp -= foe.getDmg();
	if (hp <= 0) { hp = 0; }
}

void Character::OnePunch(Character& foe)
{
	foe.DMGTaken(*this);
}
