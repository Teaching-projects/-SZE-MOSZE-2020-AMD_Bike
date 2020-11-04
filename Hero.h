#ifndef HERO_H
#define HERO_H

#include <string>
#include <fstream>
#include <map>
#include "Monster.h"

class Hero {
private:
	std::string name;
	int hp;
	int maxhp;
	int dmg;
	double acd;
	int expperlvl;
	int hpperlvl;
	int dmgperlvl;
	double acdperlvl;
	int level;
	int aktxp;

public:
	Hero(std::map <std::string, std::string> HeroData);
	static std::map <std::string, std::string> parse(std::string String);
	std::string getName();
	int getHealthPoints();
	int getDamage();
	double getAttackCoolDown();
	int getMaxHealthPoints();
	int getLevel();

	bool isAlive();
	void DMGTaken(Monster& monster);
	void OnePunch(Monster& monster);
	void LevelUp();
	void fightTilDeath(Monster& monster);
};

#endif
