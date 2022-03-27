CFLAGS=-g -W -Wall  -I/usr/local/include
LDFLAGS=-L/usr/local/lib
LIBRARIES=-lADTs

all: lab7

lab7: lab7.o
		gcc -o $@ $^ $(LIBRARIES)

lab7.o: lab7.c

clean:
		rm -f *.o lab7