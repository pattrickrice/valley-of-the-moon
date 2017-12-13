OJBS = main.o  menu.o utilities.o map.o character.o space.o \
emptySpace.o wallSpace.o keySpace.o doorSpace.o exitSpace.o \
characterSpace.o player.o gamePlay.o

CC = g++
CFLAGS = -c -std=c++0x -Wall
LFLAGS = -g -std=c++0x -Wall -o

game.o: $(OJBS)
	@echo '[BUILDING] ... game'
	@$(CC) $(LFLAGS) game $(OJBS)
	@echo '[DONE] ... Program output as: game'

main.o: main.cpp
	@echo '[BUILDING] ... main'
	@$(CC) $(CFLAGS) main.cpp

menu.o: utils/menu.cpp
	@echo '[BUILDING] ... menu'
	@$(CC) $(CFLAGS) utils/menu.cpp

utilities.o: utils/utilities.cpp
	@echo '[BUILDING] ... utilities'
	@$(CC) $(CFLAGS) utils/utilities.cpp

map.o: maps/map.cpp
	@echo '[BUILDING] ... map'
	@$(CC) $(CFLAGS) maps/map.cpp

character.o: character/character.cpp
	@echo '[BUILDING] ... character'
	@$(CC) $(CFLAGS) character/character.cpp

space.o: space/space.cpp
	@echo '[BUILDING] ... space'
	@$(CC) $(CFLAGS) space/space.cpp

emptySpace.o: space/emptySpace.cpp
	@echo '[BUILDING] ... emptySpace'
	@$(CC) $(CFLAGS) space/emptySpace.cpp

wallSpace.o: space/wallSpace.cpp
	@echo '[BUILDING] ... wallSpace'
	@$(CC) $(CFLAGS) space/wallSpace.cpp

keySpace.o: space/keySpace.cpp
	@echo '[BUILDING] ... keySpace'
	@$(CC) $(CFLAGS) space/keySpace.cpp

doorSpace.o: space/doorSpace.cpp
	@echo '[BUILDING] ... doorSpace'
	@$(CC) $(CFLAGS) space/doorSpace.cpp

characterSpace.o: space/characterSpace.cpp
	@echo '[BUILDING] ... characterSpace'
	@$(CC) $(CFLAGS) space/characterSpace.cpp

exitSpace.o: space/exitSpace.cpp
	@echo '[BUILDING] ... exitSpace'
	@$(CC) $(CFLAGS) space/exitSpace.cpp

player.o: character/player.cpp
	@echo '[BUILDING] ... player'
	@$(CC) $(CFLAGS) character/player.cpp

gamePlay.o: gamePlay.cpp
	@echo '[BUILDING] ... gamePlay'
	@$(CC) $(CFLAGS) gamePlay.cpp

clean:
	@echo '[CLEANING] ... removing .o files'
	@rm *.o

.PHONY: valgrind

valgrind:
	valgrind --tool=memcheck game