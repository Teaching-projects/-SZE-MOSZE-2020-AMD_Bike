#include "Hero.h"
#include "JSON.h"

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
	String = "test/units/" + String;
	JSON scenario = JSON::parseFromFile(String);
	if (scenario.getMap().size() != 8) {
		throw std::runtime_error("Not enough parameters!");
	}

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
		//std::cout << "LEVELUPPPPPPPPPPPPPPPPPPPPP" << std::endl;
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



