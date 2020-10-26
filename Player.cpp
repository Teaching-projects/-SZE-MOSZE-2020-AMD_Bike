#include "Player.h"
#include <iostream>
#include <cmath>

Player Player::parsePlayer(const std::string& FileName)
{
	Character parsedCharacter = Character::parseUnit(FileName);
	std::string name = parsedCharacter.getName();
	int hp = parsedCharacter.getHp();
	int dmg = parsedCharacter.getDmg();
	double attackspeed = parsedCharacter.getAttackspeed();
	return Player(name, hp, dmg, attackspeed);
}

void Player::LevelUp()
{
	MaxHp = (int)round(MaxHp * 1.1);
	dmg = (int)round(dmg * 1.1);
	hp = MaxHp;
	xp -= 100;
	attackspeed = round(attackspeed * 0.9);
}

void Player::OnePunch(Character& enemy)
{
	int CurrentXP = 0;
	if (enemy.getHp() < dmg) {
		CurrentXP = enemy.getHp();
	}
	else {
		CurrentXP = dmg;
	}
	enemy.DMGTaken(*this);
	xp += CurrentXP;
	if (xp >= 100) {
		LevelUp();
	}
}
