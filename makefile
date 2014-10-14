#Default compiler, change it for the right one that match the requirements of you S.O.
CC=g++

#Compiler flags, compile the files and show all warnings
CFLAGS=-c -Wall

all: main

main: main.o
	g++ main.o -o main

main.o: main.cpp
	g++ -c main.cpp
	
clean:
	rm -rf *o main