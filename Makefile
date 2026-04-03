# Makefile for raylib project
# This is for Makefile-beginners.
# Therefore, we only use the very fundamental rules and recipes

all: stardust

stardust: main.o Attractor.o
	g++ -o stardust main.o Attractor.o -lraylib -lX11

main.o: main.cpp Attractor.h
	g++ -c main.cpp

Attractor.o: Attractor.cpp Attractor.h
	g++ -c Attractor.cpp

clean:
	rm -f *.o stardust
