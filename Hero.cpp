#include "Hero.h"
#include "JSON.h"
#include <iostream>

Hero::Hero(const std::string& name, int hp, int dmg, double acd, const int expperlvl, const int hpperlvl, const int dmgperlvl, const double acdperlvl) :
	name(name), hp(hp), dmg(dmg), acd(acd),
	expperlvl(expperlvl),
	hpperlvl(hpperlvl),
	dmgperlvl(dmgperlvl),
	acdperlvl(acdperlvl)
{
	maxhp = hp;
	aktxp = 0;
	level = 1;
}

Hero Hero::parse(const std::string& String)
{
	JSON HeroAttributes = JSON::parseFromFile("test/units/" + String);
	if (HeroAttributes.getMapSize() != 8) {
		throw std::runtime_error("Not enough parameters!");
	}
	return Hero(HeroAttributes.get<std::string>("name"),
		HeroAttributes.get<int>("base_health_points"),
		HeroAttributes.get<int>("base_damage"),
		HeroAttributes.get<double>("base_attack_cooldown"),
		HeroAttributes.get<int>("experience_per_level"),
		HeroAttributes.get<int>("health_point_bonus_per_level"),
		HeroAttributes.get<int>("damage_bonus_per_level"),
		HeroAttributes.get<double>("cooldown_multiplier_per_level"));
}

bool Hero::isAlive() const
{
	return (hp > 0);
}

void Hero::DMGTaken(Monster& monster)
{
	hp -= monster.getDamage();
	if (hp <= 0) { hp = 0; }
}

void Hero::OnePunch(Monster& monster)
{
	int CurrentXP = 0;
	if (monster.getHealthPoints() < dmg) {
		CurrentXP = monster.getHealthPoints();
	}
	else {
		CurrentXP = dmg;
	}
	monster.DMGTaken(dmg);
	aktxp += CurrentXP;
	if (aktxp >= expperlvl) {
		LevelUp();
	}
}

void Hero::LevelUp()
{
	maxhp += hpperlvl;
	hp = maxhp;
	dmg += dmgperlvl;
	acd *= acdperlvl;
	aktxp -= expperlvl;
	level += 1;
}

void Hero::fightTilDeath(Monster& monster)
{
	double gameprogress = 0;
	double aktAS1 = acd;
	double aktAS2 = monster.getAttackCoolDown();
	while (this->isAlive() && monster.isAlive()) {
		if ((aktAS1 - gameprogress) < (aktAS2 - gameprogress)) {
			this->OnePunch(monster);
			gameprogress = aktAS1;
			aktAS1 += acd;
		}
		else if ((aktAS1 - gameprogress) > (aktAS2 - gameprogress)) {
			this->DMGTaken(monster);
			gameprogress = aktAS2;
			aktAS2 += monster.getAttackCoolDown();
		}
		else {
			this->OnePunch(monster);
			if (monster.isAlive()) {
				this->DMGTaken(monster);
			}
			aktAS1 += acd;
			aktAS2 += monster.getAttackCoolDown();
			gameprogress = aktAS1;
		}

	}
}

int Hero::getLevel() const
{
	return level;
}

std::string Hero::getName() const
{
	return name;
}

int Hero::getHealthPoints() const
{
	return hp;
}

int Hero::getDamage() const
{
	return dmg;
}

double Hero::getAttackCoolDown() const
{
	return acd;
}

int Hero::getMaxHealthPoints() const
{
	return maxhp;
}



