#include "Character.h"

Character::Character(const std::string name, const int hp, const int dmg) : name(name), hp(hp), dmg(dmg)
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

void Character::DMGTaken(const Character character)
{
	hp -= character.getDmg();
	if (hp <= 0) { hp = 0; }
}

bool Character::IsDead() const
{
	if (hp == 0) { return true; }
	else { return false; }
}

Character Character::parseUnit(const std::string& FileName)
{
	std::ifstream file;
	std::string line, name;
	int hp, dmg;
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
				dmg = stoi(line.substr(x + 2));
			}
			i++;
		}
	}
	else {
		throw 1;
	}

	file.close();
	return Character(name, hp, dmg);

}

