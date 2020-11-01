cmake_minimum_required(VERSION 2.6)

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})
 
add_library(codeToTest ../JsonParser.cpp)
add_library(codeToTest ../Player.cpp)
add_executable(ParserTest UnitTest.cpp)
add_executable(NewUnitTests UnitTest.cpp)

target_link_libraries(ParserTest ${GTEST_LIBRARIES} pthread codeToTest)
target_link_libraries(NewUnitTests ${GTEST_LIBRARIES} pthread codeToTest)