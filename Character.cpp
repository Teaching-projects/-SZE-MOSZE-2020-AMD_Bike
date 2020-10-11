#include "Character.h"
#include "JsonParser.h"

Character::Character(const std::string name, const int hp, const int dmg, const double attackspeed) : name(name), hp(hp), dmg(dmg), attackspeed(attackspeed)
{
}

std::string Character::getName() const
{
	return name;
}

int Character::getHp() const
{
	return hp;
}

int Character::getDmg() const
{
	return dmg;
}

double Character::getAttackspeed() const
{
	return attackspeed;
}

bool Character::IsDead() const
{
	return hp == 0;
}

Character Character::parseUnit(const std::string& Data)
{
	std::map<std::string, std::string> character;
	character = JsonParser::Parser(Data);
	return Character(character["name"], stoi(character["hp"]), stoi(character["dmg"]), stod(character["attackspeed"]));
}

void Character::DMGTaken(Character& foe)
{
	hp -= foe.getDmg();
	if (hp <= 0) { hp = 0; }
}

void Character::OnePunch(Character& foe)
{
	foe.DMGTaken(*this);
}
