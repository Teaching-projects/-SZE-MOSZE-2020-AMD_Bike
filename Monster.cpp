#include "Monster.h"
#include <vector>

Monster::Monster(const std::string name, int hp, int physicaldmg, int magicaldmg, int def, double acd) : name(name), hp(hp), dmg{ physicaldmg, magicaldmg }, def(def), acd(acd)
{
}

std::string Monster::getName() const
{
	return name;
}

Damage Monster::getDamage() const {
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

Monster Monster::parse(const std::string& String)
{
	JSON MonsterAttributes = JSON::parseFromFile("test/units/" + String);

	std::vector<std::string> Check = { "name", "health_points", "defense", "attack_cooldown" };
	bool IsOK = true;
	for (auto& i : Check) {
		if (!MonsterAttributes.count(i)) IsOK = false;
	}

	if (!IsOK && (!MonsterAttributes.count("damage") || !MonsterAttributes.count("magical_damage"))) {
		throw std::runtime_error("Not enough parameters!");
	}
	Damage dmg;
	if (MonsterAttributes.count("damage") && !(MonsterAttributes.count("magical_damage"))) {
		dmg.physical = MonsterAttributes.get<int>("damage");
		dmg.magical = 0;
	}
	else if (!(MonsterAttributes.count("damage") && (MonsterAttributes.count("magical_damage")))) {
		dmg.physical = 0;
		dmg.magical = MonsterAttributes.get<int>("magical_damage");
	}
	else {
		dmg.physical = MonsterAttributes.get<int>("damage");
		dmg.magical = MonsterAttributes.get<int>("magical_damage");
	}

	return Monster(MonsterAttributes.get<std::string>("name"),
		MonsterAttributes.get<int>("health_points"),
		dmg.physical,
		dmg.magical,
		MonsterAttributes.get<int>("defense"),
		MonsterAttributes.get<double>("attack_cooldown"));
}

bool Monster::isAlive() const
{
	return (hp > 0);
}

void Monster::DMGTaken(int physicaldmg, int magicaldmg)
{
	if (def <= physicaldmg) {
		hp -= physicaldmg - def;
	}
	hp -= magicaldmg;
	if (hp <= 0) { hp = 0; }
}
