#include "../JSON.h"
#include "../Hero.h"
#include "../Monster.h"
#include "../Damage.h"
#include "../Map.h"
#include "../Game.h"
#include <gtest/gtest.h>

TEST(ParserTest, InputString) {
	JSON scenario = JSON::parseFromString("\"name\":\"PrinceAidanofKhanduras\",\"hp\":30,\"dmg\":3,\"attackspeed\":1.1");

	ASSERT_TRUE(scenario.get<std::string>("name") == "Prince Aidan of Khanduras");
	ASSERT_TRUE(scenario.get<int>("hp") == 30);
	ASSERT_TRUE(scenario.get<int>("dmg") == 3);
	ASSERT_TRUE(scenario.get<double>("attackspeed") == 1.1);
}

TEST(ParserTest, InputFileName) {
	Hero hero = Hero::parse("Dark_Wanderer.json");

	ASSERT_TRUE(hero.getName() == "Prince Aidan of Khanduras");
	ASSERT_TRUE(hero.getHealthPoints() == 30);
	ASSERT_TRUE(hero.getDamage().physical == 3);
	ASSERT_TRUE(hero.getDamage().magical == 1);
	ASSERT_TRUE(hero.getAttackCoolDown() == 1.1);
}

TEST(ParserTest, InputIstream) {
	std::fstream filename;

	filename.open("test/units/Dark_Wanderer.json");
	JSON scenario = JSON::parseFromFile(filename);
	filename.close();

	ASSERT_TRUE(scenario.get<std::string>("name") == "Prince Aidan of Khanduras");
	ASSERT_TRUE(scenario.get<int>("base_health_points") == 30);
	ASSERT_TRUE(scenario.get<int>("base_damage") == 3);
	ASSERT_TRUE(scenario.get<int>("base_magical_damage") == 1);
	ASSERT_TRUE(scenario.get<double>("base_attack_cooldown") == 1.1);
}

TEST(ParserTest, WrongInputFile) {
	std::string WrongInputFileName = "WrongLuke.json";
	const std::string expectedErrorMsg = "Not enough parameters!";

	try {
		Hero::parse(WrongInputFileName);
	}
	catch (std::runtime_error &e) {
		ASSERT_EQ(e.what(), expectedErrorMsg);
	}
}

TEST(ParserTest, WrongInputString) {
	std::string WrongInputString = "\"name\":\"DarthVader\",\"hp\":38k,\"dmg\":44,\"attackspeed\":3.2";
	const std::string expectedErrorMsg = "Only digit data is acceptable!";

	try {
		JSON::parseFromString(WrongInputString);
	}
	catch (std::runtime_error &e) {
		ASSERT_EQ(e.what(), expectedErrorMsg);
	}
}



TEST(NewUnitTests, MoreWhitespace) {
	JSON scenario = JSON::parseFromFile("test/units/WhitespaceLuke.json");

	ASSERT_TRUE(scenario.get<std::string>("name") == "Luke Skywalker");
	ASSERT_TRUE(scenario.get<int>("hp") == 250);
	ASSERT_TRUE(scenario.get<int>("dmg") == 27);
	ASSERT_TRUE(scenario.get<double>("attackspeed") == 1.2);
}

TEST(NewUnitTests, DifferentOrder) {
	JSON scenario = JSON::parseFromFile("test/units/DifferentLuke.json");

	ASSERT_TRUE(scenario.get<std::string>("name") == "Luke Skywalker");
	ASSERT_TRUE(scenario.get<int>("hp") == 250);
	ASSERT_TRUE(scenario.get<int>("dmg") == 27);
	ASSERT_TRUE(scenario.get<double>("attackspeed") == 1.2);
}

TEST(NewUnitTests, getNameFunction) {
	Hero Unit = Hero::parse("Dark_Wanderer.json");

	ASSERT_TRUE(Unit.getName() == "Prince Aidan of Khanduras");
}

TEST(NewUnitTests, getHpFunction) {
	Hero Unit = Hero::parse("Dark_Wanderer.json");

	ASSERT_TRUE(Unit.getHealthPoints() == 30);
}

TEST(NewUnitTests, getDmgFunction) {
	Monster Unit = Monster::parse("Zombie.json");

	ASSERT_TRUE(Unit.getDamage().physical == 6);
}

TEST(NewUnitTests, getAttackspeedFunction) {
	Monster Unit = Monster::parse("Zombie.json");

	ASSERT_TRUE(Unit.getAttackCoolDown() == 2.8);
}

TEST(NewUnitTests, isAliveTrueFunction) {
	Monster Unit = Monster::parse("Zombie.json");

	ASSERT_TRUE(Unit.isAlive());
}

TEST(NewUnitTests, isAliveFalseFunction) {
	Monster Unit = Monster::parse("Zombie.json");
	Unit.DMGTaken(11,0);

	ASSERT_FALSE(Unit.isAlive());
}

TEST(NewUnitTests, DMGTakenFunction) {
	Monster Unit = Monster::parse("Zombie.json");
	Unit.DMGTaken(6,0);

	ASSERT_TRUE(Unit.getHealthPoints() == 5);
}

TEST(NewUnitTests, OnePunchFunction) {
	Hero Unit1 = Hero::parse("Dark_Wanderer.json");
	Monster Unit2 = Monster::parse("Zombie.json");
	Unit1.OnePunch(Unit2);

	ASSERT_TRUE(Unit2.getHealthPoints() == 7);
}

TEST(NewUnitTests, LevelUpFunction) {
	Hero Unit1 = Hero::parse("Dark_Wanderer.json");
	Unit1.LevelUp();
	
	ASSERT_TRUE(Unit1.getName() == "Prince Aidan of Khanduras");
	ASSERT_TRUE(Unit1.getHealthPoints() == 35);
	ASSERT_TRUE(Unit1.getDamage().physical == 4);
	ASSERT_TRUE(Unit1.getDamage().magical == 2);
	ASSERT_DOUBLE_EQ(Unit1.getAttackCoolDown(), 0.99);
}

TEST(NewUnitTests, NoKeyError) {
	std::string NoKey = "NoKeyLuke.json";
	const std::string expectedErrorMsg = "No key given!";

	try {
		Hero::parse(NoKey);
	}
	catch (std::runtime_error &e) {
		ASSERT_EQ(e.what(), expectedErrorMsg);
	}
}

TEST(NewUnitTests, NoValueError) {
	std::string NoValue = "NoValueLuke.json";
	const std::string expectedErrorMsg = "No value given to the \"dmg\" key!";

	try {
		Hero::parse(NoValue);
	}
	catch (std::runtime_error &e) {
		ASSERT_EQ(e.what(), expectedErrorMsg);
	}
}


TEST(NewGameUnitTests, WrongIndexException) {
	Hero Unit = Hero::parse("Dark_Wanderer.json");
	Game TheGame;
	const std::string expectedErrorMsg = "The map does not exists.";

	try {
		TheGame.putHero(Unit, 1, 1);
	}
	catch (std::runtime_error &e) {
		ASSERT_EQ(e.what(), expectedErrorMsg);
	}
}

TEST(NewGameUnitTests, OccupiedException) {
	Hero Unit = Hero::parse("Dark_Wanderer.json");
	Game TheGame("Map1.json");
	const std::string expectedErrorMsg = "There is a Wall, can not place a Hero on it!";

	try {
		TheGame.putHero(Unit, 0, 0);
	}
	catch (std::runtime_error &e) {
		ASSERT_EQ(e.what(), expectedErrorMsg);
	}
}

TEST(NewGameUnitTests, AlreadyHasHeroException) {
	Hero Unit1 = Hero::parse("Dark_Wanderer.json");
	Hero Unit2 = Hero::parse("Dark_Wanderer.json");
	Game TheGame("Map1.json");
	TheGame.putHero(Unit1, 1, 1);
	const std::string expectedErrorMsg = "There is already a Hero on the map!";

	try {
		TheGame.putHero(Unit2, 1, 1);
	}
	catch (std::runtime_error &e) {
		ASSERT_EQ(e.what(), expectedErrorMsg);
	}
}

TEST(NewGameUnitTests, AlreadyHasUnitsException) {
	Hero Unit = Hero::parse("Dark_Wanderer.json");
	Game TheGame("Map1.json");
	Map Map("Map2.json");
	TheGame.putHero(Unit, 1, 1);
	const std::string expectedErrorMsg = "The map has already units on it!";

	try {
		TheGame.setMap(Map);
	}
	catch (std::runtime_error &e) {
		ASSERT_EQ(e.what(), expectedErrorMsg);
	}
}

TEST(NewGameUnitTests, NotInitializedException) {
	Game TheGame;
	const std::string expectedErrorMsg = "The map is not set or there is no Hero on the map!";

	try {
		TheGame.run();
	}
	catch (std::runtime_error &e) {
		ASSERT_EQ(e.what(), expectedErrorMsg);
	}
}

int main(int argc, char** argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}