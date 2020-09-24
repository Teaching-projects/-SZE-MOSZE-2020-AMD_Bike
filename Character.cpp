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

void Character::DMGTaken(const int dmg)
{
	hp -= dmg;
}

void Character::Dead()
{
	if (hp <= 0) {hp = 0;}
}

