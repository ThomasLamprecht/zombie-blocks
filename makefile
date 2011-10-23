CC = gcc
version = 0.1
out = zombie\ blocks.$(version)
flags = -lm -lSDL -I/usr/include/SDL

main: main.o vector.o gamelogic.o
	$(CC) -o $(out) vector.o gamelogic.o main.o $(flags)

vector.o: vector.c vector.h types.h config.h
	$(CC) -c vector.c
	
gamelogic.o: gamelogic.c gamelogic.h types.h config.h
	$(CC) -c gamelogic.c

main.o: main.c main.h types.h config.h
	$(CC) -c main.c

x86: main.o vector.o gamelogic.o
	$(CC) -o $(out)_x86 vector.o gamelogic.o main.o $(flags)

tidy:
	rm *.o

open:
	gedit main.c main.h vector.c vector.h gamelogic.c gamelogic.h types.h config.h makefile &
