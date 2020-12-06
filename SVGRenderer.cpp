#include "SVGRenderer.h"
#include <iostream>
#include <filesystem>

SVGRenderer::SVGRenderer(const std::string& String) : OString(String)
{
}

CharacterSVGRenderer::CharacterSVGRenderer(const std::string& String) : SVGRenderer(String)
{
}

ObserverSVGRenderer::ObserverSVGRenderer(const std::string& String) : SVGRenderer(String)
{
}

void ObserverSVGRenderer::render(const Game& game) const
{
	std::map<std::string, std::string> Textures = game.getTextures();
	for (const auto& AktText : Textures) {
		if (!std::filesystem::exists(AktText.second)) Textures[AktText.first] = "test/textures/NoTexture.jpg";
	}
	int Lambda = 70;
	std::ofstream svg(this->OString);
	svg << "<svg xmlns=\"http://www.w3.org/2000/svg\" width='" << game.getMap().GetTheLongestRow() * Lambda << "' height='" << game.getMap().GetMapSize() * Lambda << "'>";

	for (int y = 0; y < game.getMap().GetMapSize(); y++) {
		for (int x = 0; x < static_cast<int>(game.getMap().GetTheLongestRow()); x++) {
			if (x < static_cast<int>(game.getMap().GetRow(y).size())) {
				if (game.getHero().coord.x == x && game.getHero().coord.y == y) {
					svg << "\t<image href=\"" << Textures["HeroTexture"] << "\" width=\"" << Lambda << "\" height=\"" << Lambda << "\" x=\"" << x * Lambda << "\" y=\"" << y * Lambda << "\"/>";
				}
				else if (isdigit(game.getMapValue(y, x))) {
					svg << "\t<image href=\"" << Textures[std::string("MonsterTexture-") += game.getMapValue(y, x)] << "\" width=\"" << Lambda << "\" height=\"" << Lambda << "\" x=\"" << x * Lambda << "\" y=\"" << y * Lambda << "\"/>";
				}
				else if (game.getMap().get(x, y) == game.getMap().Free) {
					svg << "\t<image href=\"" << Textures["FreeTexture"] << "\" width=\"" << Lambda << "\" height=\"" << Lambda << "\" x=\"" << x * Lambda << "\" y=\"" << y * Lambda << "\"/>";
				}
				else {
					svg << "\t<image href=\"" << Textures["WallTexture"] << "\" width=\"" << Lambda << "\" height=\"" << Lambda << "\" x=\"" << x * Lambda << "\" y=\"" << y * Lambda << "\"/>";
				}
			}
			else {
				svg << "\t<image href=\"" << Textures["WallTexture"] << "\" width=\"" << Lambda << "\" height=\"" << Lambda << "\" x=\"" << x * Lambda << "\" y=\"" << y * Lambda << "\"/>";
			}
		}
	}
	svg << "</svg>";
}

void CharacterSVGRenderer::render(const Game& game) const
{
	std::map<std::string, std::string> Textures = game.getTextures();
	for (const auto& AktText : Textures) {
		if (!std::filesystem::exists(AktText.second)) Textures[AktText.first] = "test/textures/NoTexture.jpg";
	}
	int Lambda = 70;
	std::ofstream svg(this->OString);
	svg << "<svg xmlns=\"http://www.w3.org/2000/svg\" width='" << game.getMap().GetTheLongestRow() * Lambda << "' height='" << game.getMap().GetMapSize() * Lambda << "'>";

	int diff1, diff2, diff3, diff4;
	
	diff1 = ((game.getHero().coord.x - game.getHero().hero->getLightRadius()) > 0 ? (game.getHero().coord.x - game.getHero().hero->getLightRadius()) : 0);
	diff2 = ((game.getHero().coord.x + game.getHero().hero->getLightRadius()) < game.getMap().GetTheLongestRow() - 1 ? (game.getHero().coord.x + game.getHero().hero->getLightRadius()) : game.getMap().GetTheLongestRow() - 1);
	diff3 = ((game.getHero().coord.y - game.getHero().hero->getLightRadius()) > 0 ? (game.getHero().coord.y - game.getHero().hero->getLightRadius()) : 0);
	diff4 = ((game.getHero().coord.y + game.getHero().hero->getLightRadius()) < game.getMap().GetMapSize() - 1 ? (game.getHero().coord.y + game.getHero().hero->getLightRadius()) : game.getMap().GetMapSize() - 1);
	
	for (int y = diff3; y <= diff4; y++) {
		for (int x = diff1; x <= diff2; x++) {
			if (x < static_cast<int>(game.getMap().GetRow(y).size())) {
				if (game.getHero().coord.x == x && game.getHero().coord.y == y) { svg << "\t<image href=\"" << Textures["HeroTexture"] << "\" width=\"" << Lambda << "\" height=\"" << Lambda << "\" x=\"" << x * Lambda << "\" y=\"" << y * Lambda << "\"/>"; }
				else if (isdigit(game.getMapValue(y, x))) {
					svg << "\t<image href=\"" << Textures[std::string("MonsterTexture-") += game.getMapValue(y, x)] << "\" width=\"" << Lambda << "\" height=\"" << Lambda << "\" x=\"" << x * Lambda << "\" y=\"" << y * Lambda << "\"/>";
				}
				else if (game.getMap().get(x, y) == game.getMap().Free) { svg << "\t<image href=\"" << Textures["FreeTexture"] << "\" width=\"" << Lambda << "\" height=\"" << Lambda << "\" x=\"" << x * Lambda << "\" y=\"" << y * Lambda << "\"/>"; }
				else { svg << "\t<image href=\"" << Textures["WallTexture"] << "\" width=\"" << Lambda << "\" height=\"" << Lambda << "\" x=\"" << x * Lambda << "\" y=\"" << y * Lambda << "\"/>"; }
			}
			else { svg << "\t<image href=\"" << Textures["WallTexture"] << "\" width=\"" << Lambda << "\" height=\"" << Lambda << "\" x=\"" << x * Lambda << "\" y=\"" << y * Lambda << "\"/>"; }
		}
	}
	svg << "</svg>";
}