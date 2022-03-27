CFLAGS=-g -W -Wall -I/usr/local/include
LDFLAGS=-L/usr/local/lib
LIBRARIES=-lADTs
PROGRAM=reverse
OBJECTS=reverse.o stringlist.o

all: $(PROGRAM)

reverse: $(OBJECTS)
	gcc $(CFLAGS) $(LDFLAGS) -o $(PROGRAM) $(OBJECTS) $(LIBRARIES)

reverse.o: reverse.c stringlist.c stringlist.h

stringlist.o: stringlist.c stringlist.h

clean:
	rm -f *.o $(PROGRAM)