#ifndef PLAYER_H
#define PLAYER_H

#include "Character.h"
#include <string>
#include <fstream>

class Player : public Character {
protected:
	int xp;				///< This is the xp of an existing champion
	int MaxHp;				///< This is the MaxHp of an existing champion
	void LevelUp();				///< This is the LevelUp function
public:
	Player(const std::string &name, const int hp, int dmg, const double attackspeed, const int xp = 0) : Character(name, hp, dmg, attackspeed), xp(xp), MaxHp(hp) {}
	static Player parsePlayer(const std::string& FileName);
	void OnePunch(Character& enemy) override;
};

#endif
