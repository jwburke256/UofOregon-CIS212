CFLAGS=-g -W -Wall -I/usr/local/include
LDFLAGS=-L/usr/local/lib
LIBRARIES=-lADTs

all: lab8 lab8ADT
	
lab8: lab8.o
	gcc $(LDFLAGS) -o $@ $^ $(LIBRARIES)

lab8ADT: lab8.o llistprioqueue.o
	gcc $(LDFLAGS) -o $@ $^ $(LIBRARIES)

lab8.o: lab8.c

llistprioqueue.o: llistprioqueue.c

clean:
	rm -f *.o lab8 lab8ADT
