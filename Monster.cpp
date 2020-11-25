#include "Monster.h"
#include "JSON.h"


Monster::Monster(const std::string name, int hp, int physicaldmg, int magicaldmg, int def, double acd) : name(name), hp(hp), dmg{ physicaldmg, magicaldmg }, def(def), acd(acd)
{
}

Monster Monster::parse(const std::string& String)
{
	JSON MonsterAttributes = JSON::parseFromFile("test/units/" + String);
	if (!(MonsterAttributes.count("name") && MonsterAttributes.count("health_points") && MonsterAttributes.count("defense") && MonsterAttributes.count("attack_cooldown")
		&& (MonsterAttributes.count("damage") || MonsterAttributes.count("magical_damage")))) {
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

void Monster::DMGTaken(int physicaldmg, int magicaldmg)
{
	if (def <= physicaldmg) {
		hp -= physicaldmg - def;
	}
	hp -= magicaldmg;
	if (hp <= 0) { hp = 0; }
}
