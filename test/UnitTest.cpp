#include "../JsonParser.h"
#include "../Player.h"
#include "../Character.h"
#include <gtest/gtest.h>

TEST(ParserTest, InputString) {
	JsonParser j;
	std::map<std::string, std::string> TestMap;

	TestMap = j.ParserFromString("\"name\":\"DarthVader\",\"hp\":380,\"dmg\":44,\"attackspeed\":3.2");

	ASSERT_TRUE(TestMap["name"] == "DarthVader");
	ASSERT_TRUE(stoi(TestMap["hp"]) == 380);
	ASSERT_TRUE(stoi(TestMap["dmg"]) == 44);
	ASSERT_TRUE(stod(TestMap["attackspeed"]) == 3.2);
}

TEST(ParserTest, InputFileName) {
	JsonParser j;
	std::map<std::string, std::string> TestMap;

	TestMap = j.Parser("test/units/Luke.json");

	ASSERT_TRUE(TestMap["name"] == "Luke Skywalker");
	ASSERT_TRUE(stoi(TestMap["hp"]) == 250);
	ASSERT_TRUE(stoi(TestMap["dmg"]) == 27);
	ASSERT_TRUE(stod(TestMap["attackspeed"]) == 1.2);
}

TEST(ParserTest, InputIstream) {
	JsonParser j;
	std::map<std::string, std::string> TestMap;
	std::fstream filename;

	filename.open("test/units/Yoda.json");
	TestMap = j.Parser(filename);
	filename.close();

	ASSERT_TRUE(TestMap["name"] == "Yoda");
	ASSERT_TRUE(stoi(TestMap["hp"]) == 190);
	ASSERT_TRUE(stoi(TestMap["dmg"]) == 57);
	ASSERT_TRUE(stod(TestMap["attackspeed"]) == 2);
}

TEST(ParserTest, WrongInputFile) {
	std::string WrongInputFileName = "test/units/WrongLuke.json";

	ASSERT_THROW(JsonParser::Parser(WrongInputFileName), std::runtime_error);
}

TEST(ParserTest, WrongInputString) {
	std::string WrongInputString = "\"name\":\"DarthVader\",\"hp\":38k,\"dmg\":44,\"attackspeed\":3.2";

	ASSERT_THROW(JsonParser::Parser(WrongInputString), std::runtime_error);
}



TEST(NewUnitTests, MoreWhitespace) {
	JsonParser j;
	std::map<std::string, std::string> TestMap;

	TestMap = j.Parser("test/units/WhitespaceLuke.json");

	ASSERT_TRUE(TestMap["name"] == "Luke Skywalker");
	ASSERT_TRUE(stoi(TestMap["hp"]) == 250);
	ASSERT_TRUE(stoi(TestMap["dmg"]) == 27);
	ASSERT_TRUE(stod(TestMap["attackspeed"]) == 1.2);
}

TEST(NewUnitTests, DifferentOrder) {
	JsonParser j;
	std::map<std::string, std::string> TestMap;

	TestMap = j.Parser("test/units/DifferentLuke.json");

	ASSERT_TRUE(TestMap["name"] == "Luke Skywalker");
	ASSERT_TRUE(stoi(TestMap["hp"]) == 250);
	ASSERT_TRUE(stoi(TestMap["dmg"]) == 27);
	ASSERT_TRUE(stod(TestMap["attackspeed"]) == 1.2);
}

TEST(NewUnitTests, getNameFunction) {
	Player Unit = Player::parsePlayer("test/units/Yoda.json");

	ASSERT_TRUE(Unit.Character::getName() == "Yoda");
}

TEST(NewUnitTests, getHpFunction) {
	Player Unit = Player::parsePlayer("test/units/Vader.json");

	ASSERT_TRUE(Unit.Character::getHp() == 380);
}

TEST(NewUnitTests, getDmgFunction) {
	Player Unit = Player::parsePlayer("test/units/Luke.json");

	ASSERT_TRUE(Unit.Character::getDmg() == 27);
}

TEST(NewUnitTests, getAttackspeedFunction) {
	Player Unit = Player::parsePlayer("\"name\":\"Obi-Wan\",\"hp\":235,\"dmg\":34,\"attackspeed\":1.7");

	ASSERT_TRUE(Unit.Character::getAttackspeed() == 1.7);
}

TEST(NewUnitTests, IsDeadTrueFunction) {
	Player Unit = Player::parsePlayer("\"name\":\"DarthVader\",\"hp\":0,\"dmg\":44,\"attackspeed\":3.2");

	ASSERT_TRUE(Unit.Character::IsDead());
}

TEST(NewUnitTests, IsDeadFalseFunction) {
	Player Unit = Player::parsePlayer("test/units/Yoda.json");

	ASSERT_FALSE(Unit.Character::IsDead());
}

TEST(NewUnitTests, DMGTakenFunction) {
	Player Unit1 = Player::parsePlayer("test/units/Yoda.json");
	Character Unit2 = Character::parseUnit("test/units/Vader.json");
	Unit1.Character::DMGTaken(Unit2);

	ASSERT_TRUE(Unit1.getHp() == 146);
}

TEST(NewUnitTests, OnePunchFunction) {
	Player Unit1 = Player::parsePlayer("test/units/Luke.json");
	Character Unit2 = Character::parseUnit("\"name\":\"Obi-Wan\",\"hp\":235,\"dmg\":34,\"attackspeed\":1.7");
	Unit1.Character::OnePunch(Unit2);

	ASSERT_TRUE(Unit2.getHp() == 208);
}

TEST(NewUnitTests, LevelUpFunction) {
	Player Unit1 = Player::parsePlayer("\"name\":\"MaceWindu\",\"hp\":290,\"dmg\":100,\"attackspeed\":6.4");
	Character Unit2 = Character::parseUnit("test/units/Luke.json");
	Unit1.Character::OnePunch(Unit2);
	
	ASSERT_TRUE(Unit1.Character::getName() == "MaceWindu");
	ASSERT_TRUE(Unit1.Character::getHp() == 319);
	ASSERT_TRUE(Unit1.Character::getDmg() == 110);
	ASSERT_TRUE(Unit1.Character::getAttackspeed() == 5.76);
}

TEST(NewUnitTests, NoKeyError) {
	std::string NoKey = "test/units/NoKeyLuke.json";

	ASSERT_THROW(JsonParser::Parser(NoKey), std::runtime_error);
}

TEST(NewUnitTests, NoValueError) {
	std::string NoValue = "test/units/NoValueLuke.json";

	ASSERT_THROW(JsonParser::Parser(NoValue), std::runtime_error);
}

int main(int argc, char** argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}