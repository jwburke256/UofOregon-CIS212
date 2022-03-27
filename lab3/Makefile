CFLAGS=-g -W -Wall
PROGRAMS=lab3

all: $(PROGRAMS)

lab3: lab3.o
	gcc -o lab3 $^

lab3.o: lab3.c

clean:
	rm -f $(PROGRAMS) *.o
