OBJS := main.o Hero.o Monster.o JSON.o
CFLAGS := -Wall -Werror -Wextra -std=c++17
CC := g++
CHMD := chmod +x
CPPOBJECTS:=JSON.cpp main.cpp Hero.cpp Monster.cpp
CFW := check_for_warning.sh
CFE := check_for_error.sh
TSH := test.sh
T := test

main: $(OBJS)
	$(CC) $(CFLAGS) -o main $(OBJS)

main.o: main.cpp Hero.h Monster.h JSON.h
	$(CC) $(CFLAGS) -c main.cpp
	
Hero.o: Hero.cpp Hero.h JSON.h
	$(CC) $(CFLAGS) -c Hero.cpp

Monster.o: Monster.cpp Monster.h JSON.h
	$(CC) $(CFLAGS) -c Monster.cpp

JsonParser.o: JSON.cpp JSON.h
	$(CC) $(CFLAGS) -c JSON.cpp

documentation:
	doxygen doxconf

sca:
	cppcheck $(CPPOBJECTS) --enable=all --output-file=cppcheck_output.txt && $(CHMD) $(CFW) && ./$(CFW) && $(CHMD) $(CFE) && ./$(CFE)

sca-test: sca-build valgrind-check io-tests

sca-build:
	$(CC) $(CFLAGS) -Werror -Wextra $(CPPOBJECTS) -o main

valgrind-check:
	valgrind --leak-check=full --error-exitcode=1 ./main $(T)/units/Blood_Raven.json $(T)/units/Dark_Wanderer.json

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
