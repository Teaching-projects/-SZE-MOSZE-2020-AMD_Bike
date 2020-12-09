#include "Hero.h"
#include <vector>

Hero::Hero(const std::string& name, int hp, int physicaldmg, int magicaldmg, int def, double acd, const int expperlvl, const int hpperlvl, const int physicaldmgperlvl, const int magicaldmgperlvl, const int defperlvl, const double acdperlvl, int lightradius, int lightradiusperlvl, std::string texture) :
	name(name), hp(hp), dmg{ physicaldmg, magicaldmg }, def(def), acd(acd), 
	expperlvl(expperlvl),
	hpperlvl(hpperlvl),
	physicaldmgperlvl(physicaldmgperlvl),
	magicaldmgperlvl(magicaldmgperlvl),
	defperlvl(defperlvl),
	acdperlvl(acdperlvl),
	lightradius(lightradius),
	lightradiusperlvl(lightradiusperlvl),
	texture(texture)
{
	maxhp = hp;
	aktxp = 0;
	level = 1;
}

std::string Hero::getName() const
{
	return name;
}

int Hero::getHealthPoints() const
{
	return hp;
}

Damage Hero::getDamage() const
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

int Hero::getLevel() const
{
	return level;
}

int Hero::getLightRadius() const
{
	return lightradius;
}

std::string Hero::getTexture() const
{
	return texture;
}

Hero Hero::parse(const std::string& String)
{
	JSON HeroAttributes = JSON::parseFromFile("test/units/" + String);
	std::vector<std::string> Check = { "name", "base_health_points", "base_defense", "base_attack_cooldown", "experience_per_level", "health_point_bonus_per_level", "defense_bonus_per_level", "cooldown_multiplier_per_level", "light_radius" };
	bool IsOK = true;

	for (auto& i : Check) {
		if (!HeroAttributes.count(i)) IsOK = false;
	}
	if (!IsOK && ((!HeroAttributes.count("base_damage") && !HeroAttributes.count("damage_bonus_per_level")) || (!HeroAttributes.count("base_magical_damage") && !HeroAttributes.count("magical_damage_bonus_per_level")))) {
		throw std::runtime_error("Not enough parameters!");
	}
	int physicaldmgperlvl, magicaldmgperlvl;
	int lightradiusperlvl = 1;
	Damage dmg;
	std::string heroTexture = "test/textures/NoTexture.jpg";
	if (HeroAttributes.count("base_damage") && !(HeroAttributes.count("base_magical_damage"))) {
		dmg.physical = HeroAttributes.get<int>("base_damage");
		physicaldmgperlvl = HeroAttributes.get<int>("damage_bonus_per_level");
		dmg.magical = 0;
		magicaldmgperlvl = 0;
	}
	else if (!(HeroAttributes.count("base_damage") && (HeroAttributes.count("base_magical_damage")))) {
		dmg.physical = 0;
		physicaldmgperlvl = 0;
		dmg.magical = HeroAttributes.get<int>("base_magical_damage");
		magicaldmgperlvl = HeroAttributes.get<int>("magical_damage_bonus_per_level");
	}
	else {
		dmg.physical = HeroAttributes.get<int>("base_damage");
		physicaldmgperlvl = HeroAttributes.get<int>("damage_bonus_per_level");
		dmg.magical = HeroAttributes.get<int>("base_magical_damage");
		magicaldmgperlvl = HeroAttributes.get<int>("magical_damage_bonus_per_level");
	}
	if(HeroAttributes.count("light_radius_bonus_per_level")) lightradiusperlvl = HeroAttributes.get<int>("light_radius_bonus_per_level");
	if (HeroAttributes.count("texture")) heroTexture = HeroAttributes.get<std::string>("texture");

	return Hero(HeroAttributes.get<std::string>("name"),
		HeroAttributes.get<int>("base_health_points"),
		dmg.physical,
		dmg.magical,
		HeroAttributes.get<int>("base_defense"),
		HeroAttributes.get<double>("base_attack_cooldown"),
		HeroAttributes.get<int>("experience_per_level"),
		HeroAttributes.get<int>("health_point_bonus_per_level"),
		physicaldmgperlvl,
		magicaldmgperlvl,
		HeroAttributes.get<int>("defense_bonus_per_level"),
		HeroAttributes.get<double>("cooldown_multiplier_per_level"), 
		HeroAttributes.get<int>("light_radius"),
		lightradiusperlvl,
		heroTexture);
}

bool Hero::isAlive() const
{
	return (hp > 0);
}

void Hero::DMGTaken(Monster& monster)
{
	if (def <= monster.getDamage().physical) {
		hp -= monster.getDamage().physical - def;
	}
	hp -= monster.getDamage().magical;
	if (hp <= 0) { hp = 0; }
}

void Hero::OnePunch(Monster& monster)
{
	int HPBeforeDamage = monster.getHealthPoints();
	monster.DMGTaken(dmg.physical, dmg.magical);
	aktxp += HPBeforeDamage - monster.getHealthPoints();
	if (aktxp >= expperlvl) {
		LevelUp();
	}
}

void Hero::LevelUp()
{
	maxhp += hpperlvl;
	hp = maxhp;
	dmg.physical += physicaldmgperlvl;
	dmg.magical += magicaldmgperlvl;
	def += defperlvl;
	acd *= acdperlvl;
	aktxp -= expperlvl;
	level += 1;
	lightradius += lightradiusperlvl;
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
