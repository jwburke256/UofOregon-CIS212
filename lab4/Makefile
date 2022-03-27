CFLAGS=-g 
PROGRAMS=lab4


all: $(PROGRAMS)

lab4: lab4.o
	gcc -o $@ $^

lab4.o: lab4.c

clean:
	rm -f $(PROGRAMS) *.o
