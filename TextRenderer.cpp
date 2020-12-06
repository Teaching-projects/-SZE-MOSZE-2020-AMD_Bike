#include "TextRenderer.h"
#include <iostream>

void TextRenderer::setOutputStream(std::ostream& Stream)
{
	OStream.copyfmt(Stream);
}

void HeroTextRenderer::render(const Game& game) const
{
	int diff1, diff2, diff3, diff4;
	OStream << "╔";

	diff1 = ((game.getHero().coord.x - game.getHero().hero->getLightRadius()) > 0 ? (game.getHero().coord.x - game.getHero().hero->getLightRadius()) : 0);
	diff2 = ((game.getHero().coord.x + game.getHero().hero->getLightRadius()) < game.getMap().GetTheLongestRow() - 1 ? (game.getHero().coord.x + game.getHero().hero->getLightRadius()) : game.getMap().GetTheLongestRow() - 1);
	diff3 = ((game.getHero().coord.y - game.getHero().hero->getLightRadius()) > 0 ? (game.getHero().coord.y - game.getHero().hero->getLightRadius()) : 0);
	diff4 = ((game.getHero().coord.y + game.getHero().hero->getLightRadius()) < game.getMap().GetMapSize() - 1 ? (game.getHero().coord.y + game.getHero().hero->getLightRadius()) : game.getMap().GetMapSize() - 1);
	for (int i = diff1; i <= diff2; i++) {
		OStream << "══";
	}
	OStream << "╗" << std::endl;
	for (int y = diff3; y <= diff4; y++) {
		OStream << "║";
		for (int x = diff1; x <= diff2; x++) {
			if (x < static_cast<int>(game.getMap().GetRow(y).size())) {
				if (game.getHero().coord.x == x && game.getHero().coord.y == y) { OStream << "┣┫"; }
				else if (game.countMonsters(x, y) >= 1) {
					if (game.countMonsters(x, y) == 1) { OStream << "M░"; }
					else { OStream << "MM"; }
				}
				else if (game.getMap().get(x, y) == game.getMap().Free) { OStream << "░░"; }
				else { OStream << "██"; }
			}
			else { OStream << "██"; }
		}
		OStream << "║" << std::endl;
	}
	OStream << "╚";
	for (int i = diff1; i <= diff2; i++) {
		OStream << "══";
	}
	OStream << "╝" << std::endl;

}

void ObserverTextRenderer::render(const Game& game) const
{
	OStream << "╔";
	for (int i = 0; i < game.getMap().GetTheLongestRow(); i++) {
		OStream << "══";
	}
	OStream << "╗" << std::endl;
	for (int y = 0; y < game.getMap().GetMapSize(); y++) {
		OStream << "║";
		for (int x = 0; x < static_cast<int>(game.getMap().GetRow(y).size()); x++) {
			if (game.getMap().get(x, y) == game.getMap().Wall) { OStream << "██"; }
			else if (game.getHero().coord.x == x && game.getHero().coord.y == y) { OStream << "┣┫"; }
			else if (game.countMonsters(x, y) >= 1) {
				if (game.countMonsters(x, y) == 1) { OStream << "M░"; }
				else { OStream << "MM"; }
			}
			else { OStream << "░░"; }
		}
		if (static_cast<int>(game.getMap().GetRow(y).size()) < game.getMap().GetTheLongestRow()) {
			for (int i = static_cast<int>(game.getMap().GetRow(y).size()); i < game.getMap().GetTheLongestRow(); i++) {
				OStream << "██";
			}
		}
		OStream << "║" << std::endl;
	}
	OStream << "╚";
	for (int i = 0; i < game.getMap().GetTheLongestRow(); i++) {
		OStream << "══";
	}
	OStream << "╝" << std::endl;
}
