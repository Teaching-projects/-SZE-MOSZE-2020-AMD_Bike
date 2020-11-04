#ifndef MONSTER_H
#define MONSTER_H

#include <string>
#include <map>

class Monster {
private:
	std::string name;
	int hp;
	int dmg;
	double acd;
	std::string race;
	std::string lore;

public:
	Monster(std::map <std::string, std::string> MonsterData);
	static std::map <std::string, std::string> parse(std::string String);
	std::string getName();
	int getDamage();
	int getHealthPoints();
	double getAttackCoolDown();

	bool isAlive();
	void DMGTaken(int dmg);
};


#endif
