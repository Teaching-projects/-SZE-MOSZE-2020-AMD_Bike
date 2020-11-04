/**
* \class Character
*
* \brief Character class
*
* This class contains all the data what an existing champion requires. Like the hp, the damage, and the attack cooldown. <br> With theese parameters, we made some functions, to modell a figth, where 2 characters are hitting each other, until one of them dies. <br> The one, who still stands after the fight, is the winner!
*
* \author skrobi12, hajdunorbi, Szabi1104
*
* \version 2.0
*
* \date 2020/10/26 19:17
*/

#ifndef CHARACTER_H
#define CHARACTER_H

#include <string>
#include <fstream>

class Character {

protected:
	const std::string name;				///< This is the name of an existing champion
	int hp;								///< This is the hitpoint of an existing champion
	int dmg;						///< This is the damage of an existing champion
	double attackspeed;			///< This is the attack cooldown of an existing champion 
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
	*/
	Character(const std::string name, const int hp, const int dmg, const double attackspeed);
	/**
	* \brief This is a getter function, that returns the champion name.
	* \param none
	* \return Returns the character's name.
	*
	*/
	std::string getName() const;
	/**
	* \brief This is a getter function, that returns the champion hitpoint.
	* \param none
	* \return Returns the character's hitpoint.
	*
	*/
	int getHp() const;
	/**
	* \brief This is a getter function, that returns the champion damage.
	* \param none
	* \return Returns the character's damage.
	*
	*/
	int getDmg() const;
	/**
	* \brief This is a getter function, that returns the champion attack cooldown.
	* \param none
	* \return Returns the character's attacspeed.
	*
	*/
	double getAttackspeed() const;
	/**
	* \brief This is a bool function, that returns 'true', when one of the champions dies, and 'false', if it lives.
	* \param none
	* \return Returns true, if the target Character's hp=0, and false if it is not.
	*
	*/
	bool IsDead() const;
	/**
	* \brief This function reads the Characters specific datas, from a file.
	* \param FileName
	* \return Returns the parsed character's data.
	*
	*/
	static Character parseUnit(const std::string& FileName);
	/**
	* \brief This function reduces the Character's hitpoint.
	* \param foe
	*
	*/
	void DMGTaken(Character& foe);
	/**
	* \brief This function calls the DMGTaken() function.
	* \param foe
	*
	*/
	virtual void OnePunch(Character& foe);
};

#endif
