#include "Player.h"
#include <iostream>
#include <cmath>

Player::~Player() 
{
}

int Player::getXp() const
{
	return xp;
}

Player* Player::parsePlayer(const std::string& FileName)
{
	Character* parsedCharacter = Character::parseUnit(FileName);
	std::string name = parsedCharacter->getName();
	int hp = parsedCharacter->getHp();
	int dmg = parsedCharacter->getDmg();
	delete parsedCharacter;
	return new Player(name, hp, dmg);
}

void Player::LevelUp()
{
	MaxHp = round(MaxHp * 1.1);
	dmg = round(dmg * 1.1);
	hp = MaxHp;
	xp -= 100;
}

void Player::OnePunch(Character* foe)
{
	int HPofFoe = foe->getHp();
	int CurrentXP = 0;
	if (HPofFoe < dmg) {
		CurrentXP = HPofFoe;
	}
	else {
		CurrentXP = dmg;
	}

	foe->DMGTaken(this);
	xp += CurrentXP;
	if (xp >= 100) {
		this->LevelUp();
	}
}