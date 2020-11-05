#include "Monster.h"
#include "JSON.h"

Monster::Monster(std::string name, int hp, int dmg, double acd) : name(name), hp(hp), dmg(dmg), acd(acd)
{
}

Monster Monster::parse(const std::string& String)
{
	JSON scenario = JSON::parseFromFile("test/units/" + String);
	return Monster(scenario.get<std::string>("name"),
		scenario.get<int>("base_health_points"),
		scenario.get<int>("base_damage"),
		scenario.get<double>("base_attack_cooldown"));
}

bool Monster::isAlive()
{
	return (hp > 0);
}

std::string Monster::getName()
{
	return name;
}

int Monster::getDamage()
{
	return dmg;
}

int Monster::getHealthPoints()
{
	return hp;
}

double Monster::getAttackCoolDown()
{
	return acd;
}


void Monster::DMGTaken(int dmg)
{
	hp -= dmg;
	if (hp <= 0) { hp = 0; }
}

