OBJS := main.o Hero.o Monster.o JSON.o Game.o Map.o PreparedGame.o MarkedMap.o TextRenderer.o SVGRenderer.o
CFLAGS := -Wall -Werror -Wextra -std=c++17
CC := g++-10
CHMD := chmod +x
CPPOBJECTS:=JSON.cpp main.cpp Hero.cpp Monster.cpp Map.cpp Game.cpp PreparedGame.cpp MarkedMap.cpp TextRenderer.cpp SVGRenderer.cpp
CFW := check_for_warning.sh
CFE := check_for_error.sh
TSH := test.sh
T := test

main: $(OBJS)
	$(CC) $(CFLAGS) -o main $(OBJS)

main.o: main.cpp Hero.h Monster.h JSON.h
	$(CC) $(CFLAGS) -c main.cpp
	
Hero.o: Hero.cpp Hero.h JSON.h Damage.h
	$(CC) $(CFLAGS) -c Hero.cpp

Monster.o: Monster.cpp Monster.h JSON.h Damage.h
	$(CC) $(CFLAGS) -c Monster.cpp

JsonParser.o: JSON.cpp JSON.h
	$(CC) $(CFLAGS) -c JSON.cpp
	
Map.o: Map.cpp Map.h
	$(CC) $(CFLAGS) -c Map.cpp

MarkedMap.o: MarkedMap.h MarkedMap.cpp Map.h
	$(CC) $(CFLAGS) -c MarkedMap.cpp

PreparedGame.o: Game.h Map.h PreparedGame.h
	$(CC) $(CFLAGS) -c PreparedGame.cpp
	
Game.o: Game.h Game.cpp Monster.h Map.h Hero.h
	$(CC) $(CFLAGS) -c Game.cpp

TextRenderer.o: TextRenderer.h TextRenderer.cpp Renderer.h
	$(CC) $(CFLAGS) -c TextRenderer.cpp

SVGRenderer.o: SVGRenderer.h SVGRenderer.cpp Renderer.h
	$(CC) $(CFLAGS) -c SVGRenderer.cpp

documentation:
	doxygen doxconf

sca:
	cppcheck $(CPPOBJECTS) --output-file=cppcheck_output.txt && $(CHMD) $(CFW) && ./$(CFW) && $(CHMD) $(CFE) && ./$(CFE)

sca-test: sca-build valgrind-check valgrind-check-two valgrind-check-three io-tests

sca-build:
	$(CC) $(CFLAGS) $(CPPOBJECTS) -o main

valgrind-check:
	valgrind --leak-check=full --error-exitcode=1 cat $(T)/scenarios/scenario1game.txt | ./main

valgrind-check-two:
	valgrind --leak-check=full --error-exitcode=1 cat $(T)/scenarios/preparedgame2.txt | ./main

valgrind-check-three:
	valgrind --leak-check=full --error-exitcode=1 ./main $(T)/scenarios/scenario1.json

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