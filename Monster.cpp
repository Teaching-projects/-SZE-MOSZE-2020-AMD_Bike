#include "Monster.h"
#include "JSON.h"

Monster::Monster(const std::string name, int hp, int dmg,double acd) : name(name), hp(hp), dmg(dmg), acd(acd)
{
}

Monster Monster::parse(const std::string& String)
{
	JSON MonsterAttributes = JSON::parseFromFile("test/units/" + String);
	if (MonsterAttributes.getMapSize() != 6) {
		throw std::runtime_error("Not enough parameters!");
	}
	return Monster(MonsterAttributes.get<std::string>("name"),
		MonsterAttributes.get<int>("health_points"),
		MonsterAttributes.get<int>("damage"),
		MonsterAttributes.get<double>("attack_cooldown"));
}

bool Monster::isAlive() const
{
	return (hp > 0);
}

std::string Monster::getName() const
{
	return name;
}

int Monster::getDamage() const
{
	return dmg;
}

int Monster::getHealthPoints() const
{
	return hp;
}

double Monster::getAttackCoolDown() const
{
	return acd;
}


void Monster::DMGTaken(int dmg)
{
	hp -= dmg;
	if (hp <= 0) { hp = 0; }
}

