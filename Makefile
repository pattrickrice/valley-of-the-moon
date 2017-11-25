OJBS = main.o  menu.o utilities.o bufferSim.o 
CC = g++
CFLAGS = -c -std=c++0x -Wall
LFLAGS = -std=c++0x -Wall -o

lab9.o: $(OJBS)
	@echo '[BUILDING] ... lab9'
	@$(CC) $(LFLAGS) lab9 $(OJBS)
	@echo '[DONE] ... Program output as: lab9'

main.o: main.cpp
	@echo '[BUILDING] ... main'
	@$(CC) $(CFLAGS) main.cpp

menu.o: menu.cpp
	@echo '[BUILDING] ... menu'
	@$(CC) $(CFLAGS) menu.cpp

utilities.o: utilities.cpp
	@echo '[BUILDING] ... utilities'
	@$(CC) $(CFLAGS) utilities.cpp

clean:
	@echo '[CLEANING] ... removing .o files'
	@rm *.o

.PHONY: valgrind

valgrind:
	valgrind --tool=memcheck ant

