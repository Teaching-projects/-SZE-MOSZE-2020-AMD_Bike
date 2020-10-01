#ifndef CHARACTER_H
#define CHARACTER_H

#include <string>
#include <fstream>

class Character {
private:
	const std::string name;
	int hp;
	const int dmg;
public:
	Character(const std::string name, const int hp, const int dmg);
	std::string getName() const;
	int getHp() const;
	int getDmg() const;
	void DMGTaken(const Character character);
	bool IsDead() const;
	static Character parseUnit(const std::string& FileName);
};

#endif
