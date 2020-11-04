/**
* \class Hero
*
* \brief Hero class
*
* This class contains all the data, that our Hero has. Like his/her name, hitpoints, maximum hitpoints, damage, attack cooldown. <br> By the time, as he/she wins the fights against some Monsters, gains xp, for that there is the actxp. <br> With that, the Hero can level up and the level variable shows the actual number of it. <br> By each levelup, there is an amount of absolut increase for xp, maximum hp, damage and the Hero's actual hp will be the maximum. Also every time the attack cooldown will decrease by a constant 10%. <br> We have some functions, with them we do the actual fight, hit the opposing Monster, check if our Hero is still alive and do the level up.
*
* \author skrobi12, hajdunorbi, Szabi1104
*
* \version 4.0
*
* \date 2020/11/04 19:17
*/


#ifndef HERO_H
#define HERO_H

#include <string>
#include <fstream>
#include <map>
#include "Monster.h"

class Hero {
private:
	std::string name;				///< This is the name of the Hero.
	int hp;				///< This is the Hero's actual hitpoints.
	int maxhp;				///< This is the Hero's maximum hitpoints.
	int dmg;				///< This is the damage of the Hero.
	double acd;				///< This is the attack cooldown of the Hero.
	int expperlvl;				///< This is the amount of xp, which the Hero gains by each level up.
	int hpperlvl;				///< This is the amount of hitpoints, which the Hero gains by each level up.
	int dmgperlvl;				///< This is the amount of damage, which the Hero gains by each level up.
	double acdperlvl;				///< This is a multiplier for the Hero's attack cooldown by each level up.
	int level;				///< This number shows the Hero's actual level.
	int aktxp;				///< This is the Hero's actual amount of experience points.

public:
	/**
	* \brief This constructor function initializes the Hero, with the given data in the parameter.
	* \param HeroData
	* [in] This map contains all the specific data of the Hero
	*/
	Hero(std::map <std::string, std::string> HeroData);
	/**
	* \brief This function reads the Hero's specific datas, from a file.
	* \param String
	* \return Returns the Hero, all of its parameters.
	*
	*/
	static std::map <std::string, std::string> parse(std::string String);
	/**
	* \brief This is a getter function, that returns the Hero's name.
	* \param none
	* \return Returns the Hero's name.
	*
	*/
	std::string getName();
	/**
	* \brief This is a getter function, that returns the Hero's actual hitpoints.
	* \param none
	* \return Returns the Hero's actual hitpoints.
	*
	*/
	int getHealthPoints();
	/**
	* \brief This is a getter function, that returns the actual damage of the Hero.
	* \param none
	* \return Returns the actual damage of the Hero.
	*
	*/
	int getDamage();
	/**
	* \brief This is a getter function, that returns the Hero's actual attack cooldown.
	* \param none
	* \return Returns the Hero's actual attack cooldown.
	*
	*/
	double getAttackCoolDown();
	/**
	* \brief This is a getter function, that returns the maximum hitpoints of the Hero.
	* \param none
	* \return Returns the maximum hitpoints of the Hero.
	*
	*/
	int getMaxHealthPoints();
	/**
	* \brief This is a getter function, that returns the Hero's actual level.
	* \param none
	* \return Returns the Hero's actual level.
	*
	*/
	int getLevel();
	/**
	* \brief This function checks whether the Hero's hitpoints is above zero or not.
	* \param none
	* \return Returns true if the Hero's hitpoints is above zero, and false if it's not.
	*
	*/
	bool isAlive();
	/**
	* \brief This function reduces the Hero's hitpoint.
	* \param monster
	*
	*/
	void DMGTaken(Monster& monster);
	/**
	* \brief This function calls the DMGTaken() function and specifies the actual amount of xp, which the Hero gains and calls the LevelUp() if needed.
	* \param monster
	*
	*/
	void OnePunch(Monster& monster);
	/**
	* \brief This function does the level up.
	* \param none
	*
	*/
	void LevelUp();
	/**
	* \brief This function fights the Hero with the actual opposing Monster, until either of them dies.
	* \param monster
	*
	*/
	void fightTilDeath(Monster& monster);
};

#endif
