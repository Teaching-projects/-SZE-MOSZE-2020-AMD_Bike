#include "../JsonParser.h"
#include <gtest/gtest.h>

TEST(ParserTest, InputString) {
	JsonParser j;
	std::map<std::string, std::string> TestMap;

	TestMap = j.ParserFromString("\"name\":\"DarthVader\",\"hp\":380,\"dmg\":44,\"attackspeed\":3.2");

	ASSERT_TRUE(TestMap["name"] == "DarthVader");
	ASSERT_TRUE(stoi(TestMap["hp"]) == 380);
	ASSERT_TRUE(stoi(TestMap["dmg"]) == 44);
	ASSERT_TRUE(stoi(TestMap["attackspeed"]) == 3.2);
}

TEST(ParserTest, InputFileName) {
	JsonParser j;
	std::map<std::string, std::string> TestMap;

	TestMap = j.Parser("test/units/Luke.json");

	ASSERT_TRUE(TestMap["name"] == "Luke Skywalker");
	ASSERT_TRUE(stoi(TestMap["hp"]) == 250);
	ASSERT_TRUE(stoi(TestMap["dmg"]) == 27);
	ASSERT_TRUE(stoi(TestMap["attackspeed"]) == 1.2);
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
	ASSERT_TRUE(stoi(TestMap["attackspeed"]) == 2);
}

TEST(ParserTest, WrongInputFile) {
	std::string WrongInputFileName = "test/units/WrongLuke.json";

	ASSERT_THROW(JsonParser::Parser(WrongInputFileName), std::runtime_error);
}

TEST(ParserTest, WrongInputString) {
	std::string WrongInputString = "\"name\":\"DarthVader\",\"hp\":38k,\"dmg\":44,\"attackspeed\":3.2";

	ASSERT_THROW(JsonParser::Parser(WrongInputString), std::runtime_error);
}

int main(int argc, char** argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}