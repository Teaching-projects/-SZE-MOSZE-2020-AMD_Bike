#include "Monster.h"
#include "JSON.h"

Monster::Monster(std::map<std::string, std::string> MonsterData) :
name(MonsterData["name"]),
hp(stoi(MonsterData["health_points"])),
dmg(stoi(MonsterData["damage"])),
acd(stod(MonsterData["attack_cooldown"])),
race(MonsterData["race"]),
lore(MonsterData["lore"])
{
}

std::map<std::string, std::string> Monster::parse(std::string String)
{
	String = "test/units/" + String;
	JSON scenario = JSON::parseFromFile(String);

	return scenario.getMap();
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

