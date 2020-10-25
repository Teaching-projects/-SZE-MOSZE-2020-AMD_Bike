#include "../JsonParser.h"
#include <gtest/gtest.h>

TEST(ParserTest, InputString) {
	JsonParser j;
	std::map<std::string, std::string> TestMap;

	TestMap = j.ParserFromString("\"name\":\"DarthVader\",\"hp\":3800,\"dmg\":270");

	ASSERT_TRUE(TestMap["name"] == "DarthVader");
	ASSERT_TRUE(stoi(TestMap["hp"]) == 3800);
	ASSERT_TRUE(stoi(TestMap["dmg"]) == 270);
}

TEST(ParserTest, InputFileName) {
	JsonParser j;
	std::map<std::string, std::string> TestMap;

	TestMap = j.Parser("test/units/Luke.json");

	ASSERT_TRUE(TestMap["name"] == "Luke Skywalker");
	ASSERT_TRUE(stoi(TestMap["hp"]) == 2500);
	ASSERT_TRUE(stoi(TestMap["dmg"]) == 440);
}

TEST(ParserTest, InputIstream) {
	JsonParser j;
	std::map<std::string, std::string> TestMap;
	std::fstream filename;

	filename.open("test/units/Yoda.json");
	TestMap = j.Parser(filename);
	filename.close();

	ASSERT_TRUE(TestMap["name"] == "Yoda");
	ASSERT_TRUE(stoi(TestMap["hp"]) == 1900);
	ASSERT_TRUE(stoi(TestMap["dmg"]) == 570);
}

TEST(UnitTest, WrongInputFile) {
	ASSERT_THROW(JsonParser::Parser("test/units/WrongLuke.json"), std::runtime_error())
}

int main(int argc, char** argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}