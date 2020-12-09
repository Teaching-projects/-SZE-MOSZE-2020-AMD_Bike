#include "PreparedGame.h"

PreparedGame::PreparedGame(const std::string& prepgamename)
{
	JSON PreparedGame = JSON::parseFromFile("test/scenarios/" + prepgamename);
	std::vector<std::string> Check = { "map", "hero", "monster-1", "wall_texture", "free_texture" };
	bool IsOK = true;
	for (auto& i : Check) {
		if (!PreparedGame.count(i)) IsOK = false;
	}
	if (!IsOK) throw std::runtime_error("Not enough parameters!");
	else {
		Textures["WallTexture"] = std::string("test/textures/") += PreparedGame.get<std::string>("wall_texture");
		Textures["FreeTexture"] = std::string("test/textures/") += PreparedGame.get<std::string>("free_texture");

		MarkedMap PreparedMap(PreparedGame.get<std::string>("map"));
		GamesMap = Map(PreparedGame.get<std::string>("map"));
		Hero PreparedHero = Hero::parse(PreparedGame.get<std::string>("hero"));
		Textures["HeroTexture"] = std::string("test/textures/") += JSON::parseFromFile("test/units/" + PreparedGame.get<std::string>("hero")).get<std::string>("texture");
		MyHero.hero = new Hero(PreparedHero);
		MyHero.coord = PreparedMap.getHeroPosition();
		bool StillAMonster = true;
		int i = 1;
		while (StillAMonster) {
			char monstertype = '0' + i;
			if (PreparedGame.count(std::string("monster-") += monstertype)) {
				std::list<Coordinates> ListToLoad = PreparedMap.getMonsterPositions(monstertype);
				Monster AktMonster = Monster::parse(PreparedGame.get<std::string>(std::string("monster-") += monstertype));
				Textures[std::string("MonsterTexture-") += monstertype] = std::string("test/textures/") += JSON::parseFromFile("test/units/" + PreparedGame.get<std::string>(std::string("monster-") += monstertype)).get<std::string>("texture");
				while (!ListToLoad.empty()) {
					Monsters.push_back({ AktMonster, ListToLoad.front() });
					ListToLoad.pop_front();
				}
				i++;
			}
			else StillAMonster = false;
		}
	}
}
