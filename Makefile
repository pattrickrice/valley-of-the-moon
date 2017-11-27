OJBS = main.o  menu.o utilities.o map.o character.o space.o
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

clean:
	@echo '[CLEANING] ... removing .o files'
	@rm *.o

.PHONY: valgrind

valgrind:
	valgrind --tool=memcheck ant

