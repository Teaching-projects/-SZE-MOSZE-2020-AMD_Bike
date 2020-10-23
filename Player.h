#ifndef PLAYER_H
#define PLAYER_H

#include "Character.h"
#include <string>
#include <fstream>

class Player : public Character {
protected:
	int xp;
	int MaxHp;
	int getXp() const;
	void LevelUp();
public:
	Player(const std::string &name, const int hp, int dmg, const int xp = 0) : Character(name, hp, dmg), xp(xp), MaxHp(hp) {}
	~Player();
	static Player* parsePlayer(const std::string& FileName);
	void OnePunch(Character*& foe) override;
};

#endif
