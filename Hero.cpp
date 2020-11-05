#include "Hero.h"
#include "JSON.h"
#include <iostream>

Hero::Hero(const std::string& name, int hp, int dmg, double acd, int expperlvl, int hpperlvl, int dmgperlvl, double acdperlvl) : 
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
	JSON scenario = JSON::parseFromFile("test/units/" + String);

	return Hero(scenario.get<std::string>("name"),
		scenario.get<int>("base_health_points"),
		scenario.get<int>("base_damage"),
		scenario.get<double>("base_attack_cooldown"),
		scenario.get<int>("experience_per_level"),
		scenario.get<int>("health_point_bonus_per_level"),
		scenario.get<int>("damage_bonus_per_level"),
		scenario.get<double>("cooldown_multiplier_per_level"));
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

	/*std::cout << "Monster acd: " << monster.getAttackCoolDown() << std::endl;
	std::cout << "Hero attack" << std::endl;*/
	/*this->OnePunch(monster);
	if (monster.isAlive()) {
		std::cout << "monster attack" << std::endl;
		this->DMGTaken(monster);
	}*/
	/*std::cout << "HP: " << hp << "/" << maxhp << "\t" << "DMG:" << dmg << "\t" << "XP:" << aktxp << std::endl;
	std::cout << "HP: " << monster.getHealthPoints() << "\t" << "DMG:" << monster.getDamage() << std::endl;*/
	while (this->isAlive() && monster.isAlive()) {
		if ((aktAS1 - gameprogress) < (aktAS2 - gameprogress)) {
			//std::cout << "Hero attack" << std::endl;
			this->OnePunch(monster);
			gameprogress = aktAS1;
			aktAS1 += acd;
		}
		else if ((aktAS1 - gameprogress) > (aktAS2 - gameprogress)) {
			//std::cout << "monster attack" << std::endl;
			this->DMGTaken(monster);
			gameprogress = aktAS2;
			aktAS2 += monster.getAttackCoolDown();
		}
		else {
			//std::cout << "Hero attack" << std::endl;
			this->OnePunch(monster);
			if (monster.isAlive()) {
				//std::cout << "monster attack" << std::endl;
				this->DMGTaken(monster);
			}
			aktAS1 += acd;
			aktAS2 += monster.getAttackCoolDown();
			gameprogress = aktAS1;
		}
		/*std::cout << "HP: " << hp << "/" << maxhp << "\t" << "DMG:" << dmg << "\t" << "XP:" << aktxp << std::endl;
		std::cout << "HP: " << monster.getHealthPoints() << "\t" << monster.getDamage() << std::endl;
		std::cout << "Hero attackspeed" << acd << "\t" << "AKTAS2:" << aktAS2 << std::endl;*/

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



