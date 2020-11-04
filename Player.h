/**
* \class Player
*
* \brief Player class
*
* This is a child class which is inherited from the Character class. This class contains all of the parent class's parameters and functions. The class contains an additional function and two parameters, which are the LevelUp(), xp and MaxHp. <br> With these parameters and function we allow for a specific Player, that when it hits a Character it gains xp. When its xp reaches 100, the levelup happens and the Player's stats will improve. 
*
* \author skrobi12, hajdunorbi, Szabi1104
*
* \version 2.0
*
* \date 2020/10/26 19:17
*/

#ifndef PLAYER_H
#define PLAYER_H

#include "Character.h"
#include <string>
#include <fstream>

class Player : public Character {
protected:
	int xp;				///< This is the current amount of xp of an existing champion
	int MaxHp;				///< This is the maximum hitpoint of an existing champion
	void LevelUp();				///< This is the LevelUp function
public:
	/**
	* \brief This constructor function initializes a specific Character object, with the given parameters.
	* \param name
	* [in] This is the name of an existing champion
	*\param hp
	* [in] This is the hitpoint of an existing champion
	*\param dmg
	* [in] This is the damage of an existing champion
	*\param attackspeed
	* [in] This is the attack cooldown of an existing champion
	*\param xp
	* [in] This is the current amount of xp of an existing champion
	*\param MaxHp
	* [in] This is the maximum hitpoint of an existing champion
	*/
	Player(const std::string &name, const int hp, int dmg, const double attackspeed, const int xp = 0) : Character(name, hp, dmg, attackspeed), xp(xp), MaxHp(hp) {}
	/**
	* \brief This function reads the Players specific datas, from a file.
	* \param FileName
	* \return Returns the parsed player's data.
	*
	*/
	static Player parsePlayer(const std::string& FileName);
	/**
	* \brief This function calls the DMGTaken() function and makes the levelup.
	* \param foe
	* 
	*/
	void OnePunch(Character& enemy) override;
};

#endif
