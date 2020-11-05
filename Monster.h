/**
* \class Monster
*
* \brief Monster class
*
* This class contains all the data, that our Monster has. Like its name, hitpoints, maximum hitpoints, damage, attack cooldown, its race and lore. <br> We have two functions, with them we hit the opposing Hero and check if the Monster is still alive.
*
* \author skrobi12, hajdunorbi, Szabi1104
*
* \version 4.0
*
* \date 2020/11/04 19:17
*/


#ifndef MONSTER_H
#define MONSTER_H

#include <string>
#include <map>
#include <variant>

class Monster {
private:
	std::string name;				///< This is the name of the Monster.
	int hp;				///< This is the hitpoints of the Monster.
	int dmg;				///< This is the Monster's damage.
	double acd;				///< This is the Monster's attack cooldown.
	std::string race;				///< This marks the Monster's race.
	std::string lore;				///< This is the lore of the Monster.

public:
	/**
	* \brief This constructor function initializes the Monster, with the given data in the parameter.
	* \param MonsterData
	* [in] This map contains all the specific data of the Monster
	*/
	Monster(std::string name, int hp, int dmg, double acd);
	/**
	* \brief This function reads the Monster's specific datas, from a file.
	* \param String
	* \return Returns a Monster unit, all of its parameters.
	*
	*/
	static Monster parse(const std::string& String);
	/**
	* \brief This is a getter function, that returns the Monster's name.
	* \param none
	* \return Returns the Monster's name.
	*
	*/
	std::string getName();
	/**
	* \brief This is a getter function, that returns the Monster's actual damage.
	* \param none
	* \return Returns the Monster's actual damage.
	*
	*/
	int getDamage();
	/**
	* \brief This is a getter function, that returns the actual hitpoints of the Monster.
	* \param none
	* \return Returns the actual hitpoints of the Monster.
	*
	*/
	int getHealthPoints();
	/**
	* \brief This is a getter function, that returns the actual attack cooldown of the Monster.
	* \param none
	* \return Returns the actual attack cooldown of the Monster.
	*
	*/
	double getAttackCoolDown();
	/**
	* \brief This function checks whether the Monster's hitpoints is above zero or not.
	* \param none
	* \return Returns true if the Monster's hitpoints is above zero, and false if it's not.
	*
	*/
	bool isAlive();
	/**
	* \brief This function reduces the Monster's hitpoints by the Hero's damage.
	* \param dmg
	*
	*/
	void DMGTaken(int dmg);
};

#endif
