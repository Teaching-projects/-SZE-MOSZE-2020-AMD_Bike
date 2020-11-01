cmake_minimum_required(VERSION 2.6)

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})
 
add_library(codeToTest ../JsonParser.cpp ../Player.cpp ../Character.h)
add_executable(ParserTest UnitTest.cpp)

target_link_libraries(ParserTest ${GTEST_LIBRARIES} pthread codeToTest)