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
	if (hp == 0) { return true; } else { return false; }
}

