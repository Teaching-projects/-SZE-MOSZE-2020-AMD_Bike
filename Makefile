OBJS := main.o Character.o Player.o JsonParser.o
CLFLAGS := -Wall -std=c++17
CC := g++
CHMD := chmod +x
CPPOBJECTS:=JsonParser.cpp main.cpp Character.cpp Player.cpp
CFW := check_for_warning.sh
CFE := check_for_error.sh
TSH := test.sh
T := test

main: $(OBJS)
	$(CC) $(CFLAGS) -o main $(OBJS)

main.o: main.cpp Player.h Character.h JsonParser.h
	$(CC) $(CFLAGS) -c main.cpp
	
Character.o: Character.cpp Character.h JsonParser.h
	$(CC) $(CFLAGS) -c Character.cpp

Player.o: Player.cpp Player.h
	$(CC) $(CFLAGS) -c Player.cpp

JsonParser.o: JsonParser.cpp JsonParser.h
	$(CC) $(CFLAGS) -c JsonParser.cpp

documentation:
	doxygen doxconf

cppcheck:
	cppcheck $(CPPOBJECTS) --enable=all --output-file=cppcheck_output.txt && $(CHMD) $(CFW) && ./$(CFW) && $(CHMD) $(CFE) && ./$(CFE)

sca-test: sca-build valgrind-check io-test

sca-build:
	$(CC) $(CFLAGS) -Werror -Wextra $(CPPOBJECTS) -o main

valgrind-check:
	valgrind --leak-check=full --error-exitcode=1 ./main $(T)/units/Luke.json $(T)/units/Vader.json

io-tests:
	$(CHMD) $(TSH) && ./$(TSH)

unittest: build cmake test-and-make run-unittest

build:
	$(CC) $(CFLAGS) $(CPPOBJECTS)

cmake:
	cmake $(T)/CMakeLists.txt

test-and-make:
	cd $(T) && make

run-unittest:
	$(T)/ParserTest
