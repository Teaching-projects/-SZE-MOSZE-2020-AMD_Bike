#include "Monster.h"
#include <vector>

Monster::Monster(const std::string name, int hp, int physicaldmg, int magicaldmg, int def, double acd, std::string texture) : name(name), hp(hp), dmg{ physicaldmg, magicaldmg }, def(def), acd(acd), texture(texture)
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

std::string Monster::getTexture() const
{
	return texture;
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
	std::string MonsterTexture = "test/textures/NoTexture.jpg";
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
	if (MonsterAttributes.count("texture")) MonsterTexture = MonsterAttributes.get<std::string>("texture");

	return Monster(MonsterAttributes.get<std::string>("name"),
		MonsterAttributes.get<int>("health_points"),
		dmg.physical,
		dmg.magical,
		MonsterAttributes.get<int>("defense"),
		MonsterAttributes.get<double>("attack_cooldown"),
		MonsterTexture);
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
