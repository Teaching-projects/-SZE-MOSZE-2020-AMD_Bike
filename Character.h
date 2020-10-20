/**
 * \class Character
 * 
 * \brief Character class
 *
 * This class contains all the data what an existing champion requires. Like the hp, the damage, and the attack cooldown. <br> With theese parameters, we made some functions, to modell a figth, where 2 characters are hitting each other, until one of them dies. <br> The one, who still stands after the fight, is the winner!
 * 
 * \author skrobi12
 * 
 * \version 1.0
 * 
 * \date 2020/10/06 18:17
 */

#ifndef CHARACTER_H
#define CHARACTER_H

#include <string>
#include <fstream>

class Character {
private:
	const std::string name;				///< This is the name of an existing champion
	int hp;								///< This is the hitpoint of an existing champion
	const int dmg;						///< This is the damage of an existing champion
	const double attackspeed;			///< This is the attack cooldown of an existing champion
	void DMGTaken(const Character character); 
	friend void Fight(Character character1, Character character2);
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
	 * 
	 */
	std::string getName() const;
	/**
	 * \brief This is a getter function, that returns the champion hitpoint.
	 * \param none
	 *
	 */
	int getHp() const;
	/**
	 * \brief This is a getter function, that returns the champion damage.
	 * \param none
	 *
	 */
	int getDmg() const;
	/**
	 * \brief This is a getter function, that returns the champion attack cooldown.
	 * \param none
	 *
	 */
	double getAttackspeed() const;
	/**
	 * \brief This is a bool function, that returns 'true', when one of the champions dies, and 'false', if it lives.
	 * \param none
	 *
	 */
	bool IsDead() const;
	/**
	 * \brief This function reads the Characters specific datas, from a file.
	 * \param FileName
	 *
	 */
	static Character parseUnit(const std::string FileName);
};

#endif