/**
* \struct Damage
*
* \brief Damage struct 
*
* This struct contains all the base calculations, and the '<<' operator which is used in the main function.
*
* \author skrobi12, hajdunorbi, Szabi1104
*
* \version 6.0
*
* \date 2020/11/22 19:17
*/

#ifndef DAMAGE_H
#define DAMAGE_H

#include <string>
#include <iostream>

struct Damage {
	int physical;		///< This is the physical damage of a Hero, or a Monster
	int magical;		///< This is the magical damage of a Hero, or a Monster

	Damage operator+(const Damage& dmg) {
		Damage ToReturn;
		ToReturn.physical = physical + dmg.physical;
		ToReturn.magical = magical + dmg.magical;
		return ToReturn;
	}

	Damage operator+=(const Damage& dmg) {
		Damage ToReturn;
		ToReturn.physical += dmg.physical;
		ToReturn.magical += dmg.magical;
		return ToReturn;
	}

	Damage operator*=(const Damage& dmg) {
		Damage ToReturn;
		ToReturn.physical *= dmg.physical;
		ToReturn.magical *= dmg.magical;
		return ToReturn;
	}

	friend std::ostream& operator<<(std::ostream& o, const Damage& dmg) {
		o << "physical " << dmg.physical << ", magical " << dmg.magical;
		return o;
	}

};

#endif
