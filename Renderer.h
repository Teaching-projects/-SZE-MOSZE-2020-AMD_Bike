/**
* \class Renderer
*
* \brief Renderer class
*
* This class is an abstract class, which has no constructor and has only one virtual function.
*
* \author skrobi12, hajdunorbi, Szabi1104
*
* \version 12.0
*
* \date 2020/12/05 19:17
*/


#ifndef RENDERER_H
#define RENDERER_H
#include "Game.h"

class Game;
class Renderer {
public:
	/**
	* \brief This is a render function.
	* \param Game&
	*
	*/
	virtual void render(const Game&) const = 0;
};

#endif
