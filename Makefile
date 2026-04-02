# Makefile for raylib project
# This is for Makefile-beginners.
# Therefore, we only use the very fundamental rules and recipes

all: stardust

stardust: main.o
	g++ -o stardust main.o -lraylib -lX11

main.o: main.cpp
	g++ -c main.cpp

clean:
	rm -f *.o stardust
