OJBS = main.o  menu.o utilities.o map.o
CC = g++
CFLAGS = -c -std=c++0x -Wall
LFLAGS = -std=c++0x -Wall -o

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

clean:
	@echo '[CLEANING] ... removing .o files'
	@rm *.o

.PHONY: valgrind

valgrind:
	valgrind --tool=memcheck ant

