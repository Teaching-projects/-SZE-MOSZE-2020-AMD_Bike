/**
* \class TextRenderer
*
* \brief TextRenderer class
*
* This class prints the map to the command output.
*
* \author skrobi12, hajdunorbi, Szabi1104
*
* \version 12.0
*
* \date 2020/12/07 19:17
*/


#ifndef TEXTRENDERER_H
#define TEXTRENDERER_H

#include <ostream>
#include "Renderer.h"

class TextRenderer : public Renderer {
protected:
	std::ostream& OStream;		///< This is pointer variable, that points to a Hero type.
public:
	/**
	* \brief This constructor function initializes the output stream.
	* \param Stream
	* [in] It defines the type of the output stream.
	*/
	TextRenderer(std::ostream& Stream = std::cout) : OStream(Stream) {}
	
	/**
	* \brief This function initializes the output stream.
	* \param Stream
	*
	*/
	void setOutputStream(std::ostream& Stream);
	
	/**
	* \brief This is a render function.
	* \param Game&
	*
	*/
	virtual void render(const Game&) const = 0;
};

class HeroTextRenderer : public TextRenderer {
public:
	/**
	* \brief This is a render function.
	* \param Game&
	*
	*/
	void render(const Game&) const override;
};

class ObserverTextRenderer : public TextRenderer {
public:
	/**
	* \brief This is a render function.
	* \param Game&
	*
	*/
	void render(const Game&) const override;
};

#endif
