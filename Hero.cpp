#include "Hero.h"
#include "JSON.h"
#include <iostream>

Hero::Hero(std::map<std::string, std::string> HeroData) :
	name(HeroData["name"]),
	maxhp(stoi(HeroData["base_health_points"])),
	dmg(stoi(HeroData["base_damage"])),
	acd(stod(HeroData["base_attack_cooldown"])),
	expperlvl(stoi(HeroData["experience_per_level"])),
	hpperlvl(stoi(HeroData["health_point_bonus_per_level"])),
	dmgperlvl(stoi(HeroData["damage_bonus_per_level"])),
	acdperlvl(stod(HeroData["cooldown_multiplier_per_level"])),
	level(1),
	aktxp(0)
{
	hp = maxhp;
}

std::map<std::string, std::string> Hero::parse(std::string String)
{
	String = "test/" + String;
	JSON scenario = JSON::parseFromFile(String);

	return scenario.getMap();
}

bool Hero::isAlive()
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

int Hero::getLevel()
{
	return level;
}

std::string Hero::getName()
{
	return name;
}

int Hero::getHealthPoints()
{
	return hp;
}

int Hero::getDamage()
{
	return dmg;
}

double Hero::getAttackCoolDown()
{
	return acd;
}

int Hero::getMaxHealthPoints()
{
	return maxhp;
}



