#include "Monster.h"
#include "JSON.h"

Monster::Monster(const std::string name, int hp, int dmg, int def, double acd) : name(name), hp(hp), dmg(dmg), def(def), acd(acd)
{
}

Monster Monster::parse(const std::string& String)
{
	JSON MonsterAttributes = JSON::parseFromFile("test/units/" + String);
	if (MonsterAttributes.getMapSize() != 7) {
		throw std::runtime_error("Not enough parameters!");
	}
	return Monster(MonsterAttributes.get<std::string>("name"),
		MonsterAttributes.get<int>("health_points"),
		MonsterAttributes.get<int>("damage"),
		MonsterAttributes.get<int>("defense"),
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
	if (def <= dmg) {
		hp -= dmg - def;
	}
	if (hp <= 0) { hp = 0; }
}
