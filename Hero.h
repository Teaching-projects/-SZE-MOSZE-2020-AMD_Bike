/**
* \class Hero
*
* \brief Hero class
*
* This class contains all the data, that our Hero has. Like his/her name, hitpoints, maximum hitpoints, damage, attack cooldown. <br> By the time, as he/she wins the fights against some Monsters, gains xp, for that there is the actxp. <br> With that, the Hero can level up and the level variable shows the actual number of it. <br> By each levelup, there is an amount of absolut increase for xp, maximum hp, damage and the Hero's actual hp will be the maximum. Also every time the attack cooldown will decrease by a constant 10%. <br> We have some functions, with them we do the actual fight, hit the opposing Monster, check if our Hero is still alive and do the level up.
*
* \author skrobi12, hajdunorbi, Szabi1104
*
* \version 6.0
*
* \date 2020/11/22 19:17
*/


#ifndef HERO_H
#define HERO_H

#include <string>
#include <fstream>
#include <map>
#include <variant>
#include "Monster.h"
#include "Damage.h"
#include "JSON.h"

class Hero {
private:
	const std::string name;					///< This is the name of the Hero.
	int hp;									///< This is the Hero's actual hitpoints.
	int maxhp;								///< This is the Hero's maximum hitpoints.
	Damage dmg;								///< This is the damage of the Hero. It can be physical, or magical.
	int def;								///< This is the defense of the Hero.
	double acd;								///< This is the attack cooldown of the Hero.
	const int expperlvl;					///< This is the amount of xp, which the Hero gains by each level up.
	const int hpperlvl;						///< This is the amount of hitpoints, which the Hero gains by each level up.
	const int physicaldmgperlvl;			///< This is the amount of physical damage, which the Hero gains by each level up.
	const int magicaldmgperlvl;				///< This is the amount of magical damage, which the Hero gains by each level up.
	const int defperlvl;					///< This is the amount of defense point, which the Hero gains by each level up.
	const double acdperlvl;					///< This is a multiplier for the Hero's attack cooldown by each level up.
	int lightradius;						///< This is the sight parameter of the Hero.
	const int lightradiusperlvl;			///< This is the amount of sight parameter, which the Hero gains by each level up.
	int level;								///< This number shows the Hero's actual level.
	int aktxp;								///< This is the Hero's actual amount of experience points.

public:
	/**
	* \brief This constructor function initializes the Hero, with the given data in the parameter.
	* \param HeroData
	* [in] This map contains all the specific data of the Hero
	*/
	Hero(const std::string& name, int hp, int physicaldmg, int magicaldmg , int def, double acd, const int expperlvl, const int hpperlvl, const int physicaldmgperlvl, const int magicaldmgperlvl, const int defperlvl, const double acdperlvl, int lightradius, int lightradiusperlvl);

	/**
	* \brief This function reads the Hero's specific datas, from a file.
	* \param String
	* \return Returns the Hero, all of its parameters.
	*
	*/static Hero parse(const std::string& String);

	/**
	* \brief This is a getter function, that returns the Hero's name.
	* \param none
	* \return Returns the Hero's name.
	*
	*/
	std::string getName() const;

	/**
	* \brief This is a getter function, that returns the Hero's actual hitpoints.
	* \param none
	* \return Returns the Hero's actual hitpoints.
	*
	*/
	int getHealthPoints() const;

	/**
	* \brief This is a getter function, that returns the actual damage of the Hero. It can be physical or magical.
	* \param none
	* \return Returns the actual physical/magical damage of the Hero.
	*
	*/
	Damage getDamage() const;

	/**
	* \brief This is a getter function, that returns the Hero's actual attack cooldown.
	* \param none
	* \return Returns the Hero's actual attack cooldown.
	*
	*/
	double getAttackCoolDown() const;

	/**
	* \brief This is a getter function, that returns the maximum hitpoints of the Hero.
	* \param none
	* \return Returns the maximum hitpoints of the Hero.
	*
	*/
	int getMaxHealthPoints() const;

	/**
	* \brief This is a getter function, that returns the Hero's actual level.
	* \param none
	* \return Returns the Hero's actual level.
	*
	*/
	int getLevel() const;

	/**
	* \brief This is a getter function, that returns the Hero's actual sight parameter.
	* \param none
	* \return Returns the Hero's actual sight parameter.
	*
	*/
	int getLightRadius() const;

	/**
	* \brief This function checks whether the Hero's hitpoints is above zero or not.
	* \param none
	* \return Returns true if the Hero's hitpoints is above zero, and false if it's not.
	*
	*/
	bool isAlive() const;

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