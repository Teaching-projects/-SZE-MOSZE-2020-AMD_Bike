/**
* \class Monster
*
* \brief Monster class
*
* This class contains all the data, that our Monster has. Like its name, hitpoints, maximum hitpoints, damage, attack cooldown, its race and lore. <br> We have two functions, with them we hit the opposing Hero and check if the Monster is still alive.
*
* \author skrobi12, hajdunorbi, Szabi1104
*
* \version 6.0
*
* \date 2020/11/22 19:17
*/


#ifndef MONSTER_H
#define MONSTER_H

#include <string>
#include <map>
#include <variant>
#include "Damage.h"
#include "JSON.h"

class Monster {
private:
	const std::string name;				///< This is the name of the Monster.
	int hp;								///< This is the hitpoints of the Monster.
	Damage dmg;							///< This is the damage of the Monster. It can be physical, or magical.								
	int def;							///< This is the defense of the Monster.
	double acd;							///< This is the Monster's attack cooldown.
	const std::string race;				///< This marks the Monster's race.
	const std::string lore;				///< This is the lore of the Monster.
	std::string texture;				///< This is the Hero image's name

public:
	/**
	* \brief This constructor function initializes the Monster, with the given data in the parameter.
	* \param MonsterData
	* [in] This map contains all the specific data of the Monster
	*/
	Monster(const std::string &name, int hp, int physicaldmg, int magicaldmg, int def, double acd, const std::string& texture);

	/**
	* \brief This is a getter function, that returns the Monster's name.
	* \param none
	* \return Returns the Monster's name.
	*
	*/
	std::string getName() const;

	/**
	* \brief This is a getter function, that returns the actual damage of the Monster. It can be physical or magical.
	* \param none
	* \return Returns the actual physical/magical damage of the Monster.
	*
	*/
	Damage getDamage() const;

	/**
	* \brief This is a getter function, that returns the actual hitpoints of the Monster.
	* \param none
	* \return Returns the actual hitpoints of the Monster.
	*
	*/
	int getHealthPoints() const;

	/**
	* \brief This is a getter function, that returns the actual attack cooldown of the Monster.
	* \param none
	* \return Returns the actual attack cooldown of the Monster.
	*
	*/
	double getAttackCoolDown() const;

	std::string getTexture() const;

	/**
	* \brief This function reads the Monster's specific datas, from a file.
	* \param String
	* \return Returns a Monster unit, all of its parameters.
	*
	*/
	static Monster parse(const std::string& String);

	/**
	* \brief This function checks whether the Monster's hitpoints is above zero or not.
	* \param none
	* \return Returns true if the Monster's hitpoints is above zero, and false if it's not.
	*
	*/
	bool isAlive() const;

	/**
	* \brief This function reduces the Monster's hitpoints by the Hero's damage.
	* \param physicaldmg
	* \param magicaldmg
	*
	*/
	void DMGTaken(int physicaldmg, int magicaldmg);
};

#endif
