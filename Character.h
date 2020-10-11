#ifndef CHARACTER_H
#define CHARACTER_H

#include <string>
#include <fstream>

class Character {
private:
	const std::string name;
	int hp;
	const int dmg;
	const double attackspeed;
	void DMGTaken(const Character character);
	friend void Fight(Character character1, Character character2);
public:
	Character(const std::string name, const int hp, const int dmg, const double attackspeed);
	std::string getName() const;
	int getHp() const;
	int getDmg() const;
	double getAttackspeed() const;
	bool IsDead() const;
	static Character parseUnit(const std::string FileName);
};

#endif