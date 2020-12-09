/**
* \class SVGRenderer
*
* \brief SVGRenderer class
*
* This class prints the map into an svg file.
*
* \author skrobi12, hajdunorbi, Szabi1104
*
* \version 12.0
*
* \date 2020/12/07 19:17
*/


#ifndef SVGRENDERER_H
#define SVGRENDERER_H

#include <fstream>
#include "Renderer.h"

class SVGRenderer : public Renderer {
protected:
	std::string OString;			///< This is string variable, to replace the cout.
public:
	/**
	* \brief This constructor function initializes the output stream.
	* \param Stream
	* [in] It defines the type of the output stream.
	*/
	SVGRenderer(const std::string& String);
	
	/**
	* \brief This is a render function.
	* \param Game&
	*
	*/
	virtual void render(const Game&) const = 0;
};

class CharacterSVGRenderer : public SVGRenderer {
public:
	/**
	* \brief This constructor function initializes the output stream.
	* \param String
	* [in] It defines the type of the output stream.
	*/
	explicit CharacterSVGRenderer(const std::string& String);

	/**
	* \brief This is a render function.
	* \param Game&
	*
	*/
	void render(const Game&) const override;
};

class ObserverSVGRenderer : public SVGRenderer {
public:
	/**
	* \brief This constructor function initializes the output stream.
	* \param String
	* [in] It defines the type of the output stream.
	*/
	explicit ObserverSVGRenderer(const std::string& String);

	/**
	* \brief This is a render function.
	* \param Game&
	*
	*/
	void render(const Game&) const override;
};

#endif
