#include "PreparedGame.h"

PreparedGame::PreparedGame(std::string prepgamename)
{
	JSON PreparedGame = JSON::parseFromFile("test/scenarios/" + prepgamename);
	if (!(PreparedGame.count("map") && PreparedGame.count("hero") && PreparedGame.count("monster-1"))) throw std::runtime_error("Not enough parameters!");
	else {
		MarkedMap PreparedMap(PreparedGame.get<std::string>("map"));
		GamesMap = Map(PreparedGame.get<std::string>("map"));
		Hero PreparedHero = Hero::parse(PreparedGame.get<std::string>("hero"));
		MyHero.hero = new Hero(PreparedHero);
		MyHero.coord = PreparedMap.getHeroPosition();

		for (int i = 1; i < PreparedGame.getMapSize() - 1; i++) {
			char monstertype = '0' + i;
			std::list<Coordinates> ListToLoad = PreparedMap.getMonsterPositions(monstertype);
			while (!ListToLoad.empty()) {
				Monster AktMonster = Monster::parse(PreparedGame.get<std::string>(std::string("monster-") += monstertype));
				Monsters.push_back({ AktMonster, ListToLoad.front()});
				ListToLoad.pop_front();
			}
		}
	}
}