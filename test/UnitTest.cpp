#include "../JsonParser.h"
#include <gtest/gtest.h>

TEST(ParserTest, InputString) {
	JsonParser j;
	std::map<std::string, std::string> TestMap;

	TestMap = j.ParserForString("\"name\":\"DarthVader\",\"hp\":3800,\"dmg\":270");

	ASSERT_TRUE(TestMap["name"] == "DarthVader");
	ASSERT_TRUE(stoi(TestMap["hp"]) == 3800);
	ASSERT_TRUE(stoi(TestMap["dmg"]) == 270);
}

TEST(ParserTest, InputFileName) {
	JsonParser j;
	std::map<std::string, std::string> TestMap;

	TestMap = j.ParserForFileName("test/units/Luke.json");

	ASSERT_TRUE(TestMap["name"] == "Luke Skywalker");
	ASSERT_TRUE(stoi(TestMap["hp"]) == 2500);
	ASSERT_TRUE(stoi(TestMap["dmg"]) == 440);
}

TEST(ParserTest, InputIstream) {
	JsonParser j;
	std::map<std::string, std::string> TestMap;
	std::fstream filename;

	filename.open("test/units/Yoda.json");
	TestMap = j.ParserForIstream(filename);
	filename.close();

	ASSERT_TRUE(TestMap["name"] == "Yoda");
	ASSERT_TRUE(stoi(TestMap["hp"]) == 1900);
	ASSERT_TRUE(stoi(TestMap["dmg"]) == 570);
}

TEST(UnitTest, WrongInputFile) {
	JsonParser j;
	std::map<std::string, std::string> TestMap;

	TestMap = j.ParserForFileName("test/units/WrongLuke.json");

	ASSERT_TRUE(TestMap["name"] == "Luke Skywalker");
	ASSERT_FALSE(stoi(TestMap["hp"]) == 2500);
	ASSERT_TRUE(stoi(TestMap["dmg"]) == 440);
}

int main(int argc, char** argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}