#include "../JSON.h"
#include "../Hero.h"
#include "../Monster.h"
#include <gtest/gtest.h>

TEST(ParserTest, InputString) {
	JSON scenario = JSON::parseFromString("\"name\":\"PrinceAidanOfKhanduras\",\"hp\":30,\"dmg\":3,\"attackspeed\":1.1");
	std::map<std::string, std::string> TestMap = scenario.getMap();

	ASSERT_TRUE(TestMap["name"] == "PrinceAidanOfKhanduras");
	ASSERT_TRUE(stoi(TestMap["hp"]) == 30);
	ASSERT_TRUE(stoi(TestMap["dmg"]) == 3);
	ASSERT_TRUE(stod(TestMap["attackspeed"]) == 1.1);
}

TEST(ParserTest, InputFileName) {
	Hero hero;
	hero.parse("test/units/Dark_Wanderer.json");

	ASSERT_TRUE(hero.getName() == "Prince Aidan of Khanduras");
	ASSERT_TRUE(hero.getHealthPoints() == 30);
	ASSERT_TRUE(hero.getDamage() == 3);
	ASSERT_TRUE(hero.getAttackCoolDown() == 1.1);
}

TEST(ParserTest, InputIstream) {
	JSON scenario;
	std::map<std::string, std::string> TestMap;
	std::fstream filename;

	filename.open("test/units/Dark_Wanderer.json");
	TestMap = scenario.parseFromFile(filename).getMap();
	filename.close();

	ASSERT_TRUE(TestMap["name"] == "Prince Aidan of Khanduras");
	ASSERT_TRUE(stoi(TestMap["base_health_points"]) == 30);
	ASSERT_TRUE(stoi(TestMap["base_damage"]) == 3);
	ASSERT_TRUE(stod(TestMap["atbase_attack_cooldowntackspeed"]) == 1.1);
}

TEST(ParserTest, WrongInputFile) {
	std::string WrongInputFileName = "test/units/WrongLuke.json";
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
	JSON scenario;
	std::map<std::string, std::string> TestMap;
	TestMap = scenario.parseFromFile("test/units/WhitespaceLuke.json");

	ASSERT_TRUE(TestMap["name"] == "Luke Skywalker");
	ASSERT_TRUE(stoi(TestMap["hp"]) == 250);
	ASSERT_TRUE(stoi(TestMap["dmg"]) == 27);
	ASSERT_TRUE(stod(TestMap["attackspeed"]) == 1.2);
}

TEST(NewUnitTests, DifferentOrder) {
	JSON scenario;
	std::map<std::string, std::string> TestMap;

	TestMap = scenario.parseFromFile("test/units/DifferentLuke.json");

	ASSERT_TRUE(TestMap["name"] == "Luke Skywalker");
	ASSERT_TRUE(stoi(TestMap["hp"]) == 250);
	ASSERT_TRUE(stoi(TestMap["dmg"]) == 27);
	ASSERT_TRUE(stod(TestMap["attackspeed"]) == 1.2);
}

TEST(NewUnitTests, getNameFunction) {
	Hero Unit = Hero::parse("test/units/Dark_Wanderer.json");

	ASSERT_TRUE(Unit.getName() == "Prince Aidan of Khanduras");
}

TEST(NewUnitTests, getHpFunction) {
	Hero Unit = Hero::parse("test/units/Dark_Wanderer.json");

	ASSERT_TRUE(Unit.getHealthPoints() == "30");
}

TEST(NewUnitTests, getDmgFunction) {
	Monster Unit = Monster::parse("test/units/Zombie.json");

	ASSERT_TRUE(Unit.getDamage() == "1");
}

TEST(NewUnitTests, getAttackspeedFunction) {
	Monster Unit = Monster::parse("test/units/Zombie.json");

	ASSERT_TRUE(Unit.getAttackCoolDown() == "2.8");
}

TEST(NewUnitTests, isAliveTrueFunction) {
	Monster Unit = Monster::parse("test/units/Zombie.json");

	ASSERT_TRUE(Unit.isAlive());
}

TEST(NewUnitTests, isAliveFalseFunction) {
	Monster Unit = Monster::parse("test/units/Zombie.json");
	Unit.DMGTaken(10);

	ASSERT_FALSE(Unit.isAlive());
}

TEST(NewUnitTests, DMGTakenFunction) {
	Monster Unit = Monster::parse("test/units/Zombie.json");
	Unit.DMGTaken(5);

	ASSERT_TRUE(Unit.getHealthPoints() == 5);
}

TEST(NewUnitTests, OnePunchFunction) {
	Hero Unit1 = Hero::parse("test/units/Dark_Wanderer.json");
	Monster Unit2 = Monster::parse("test/units/Zombie.json");
	Unit1.OnePunch(Unit2);

	ASSERT_TRUE(Unit2.getHealthPoints() == 7);
}

TEST(NewUnitTests, LevelUpFunction) {
	Hero Unit1 = Hero::parse("test/units/Dark_Wanderer.json");
	Unit1.LevelUp();
	
	ASSERT_TRUE(Unit1.getName() == "Prince Aidan of Khanduras");
	ASSERT_TRUE(Unit1.getHp() == 35);
	ASSERT_TRUE(Unit1.getDmg() == 4);
	ASSERT_DOUBLE_EQ(Unit1.getAttackspeed(), 0.99);
}

TEST(NewUnitTests, NoKeyError) {
	std::string NoKey = "test/units/NoKeyLuke.json";
	const std::string expectedErrorMsg = "No key given!";

	try {
		Hero::parse(NoKey);
	}
	catch (std::runtime_error &e) {
		ASSERT_EQ(e.what(), expectedErrorMsg);
	}
}

TEST(NewUnitTests, NoValueError) {
	std::string NoValue = "test/units/NoValueLuke.json";
	const std::string expectedErrorMsg = "No value given to the \"dmg\" key!";

	try {
		Hero::parse(NoValue);
	}
	catch (std::runtime_error &e) {
		ASSERT_EQ(e.what(), expectedErrorMsg);
	}
}

int main(int argc, char** argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}