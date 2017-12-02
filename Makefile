OJBS = main.o  menu.o utilities.o map.o character.o space.o \
emptySpace.o wallSpace.o keySpace.o doorSpace.o player.o \
gamePlay.o

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

menu.o: menu.cpp
	@echo '[BUILDING] ... menu'
	@$(CC) $(CFLAGS) menu.cpp

utilities.o: utilities.cpp
	@echo '[BUILDING] ... utilities'
	@$(CC) $(CFLAGS) utilities.cpp

map.o: map.cpp
	@echo '[BUILDING] ... map'
	@$(CC) $(CFLAGS) map.cpp

character.o: character.cpp
	@echo '[BUILDING] ... character'
	@$(CC) $(CFLAGS) character.cpp

space.o: space.cpp
	@echo '[BUILDING] ... space'
	@$(CC) $(CFLAGS) space.cpp

emptySpace.o: emptySpace.cpp
	@echo '[BUILDING] ... emptySpace'
	@$(CC) $(CFLAGS) emptySpace.cpp

wallSpace.o: wallSpace.cpp
	@echo '[BUILDING] ... wallSpace'
	@$(CC) $(CFLAGS) wallSpace.cpp

keySpace.o: keySpace.cpp
	@echo '[BUILDING] ... keySpace'
	@$(CC) $(CFLAGS) keySpace.cpp

doorSpace.o: doorSpace.cpp
	@echo '[BUILDING] ... doorSpace'
	@$(CC) $(CFLAGS) doorSpace.cpp

player.o: player.cpp
	@echo '[BUILDING] ... player'
	@$(CC) $(CFLAGS) player.cpp

gameplay.o: gamePlay.cpp
	@echo '[BUILDING] ... gamePlay'
	@$(CC) $(CFLAGS) gamePlay.cpp

clean:
	@echo '[CLEANING] ... removing .o files'
	@rm *.o

.PHONY: valgrind

valgrind:
	valgrind --tool=memcheck ant

