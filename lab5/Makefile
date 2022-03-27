CFLAGS = -g -W -Wall -I/usr/local/include
LDFLAGS = -L/usr/local/lib
OBJECTS=lab5.o
LIBRARIES=-lADTs -lm

lab5: $(OBJECTS)
	gcc $(CFLAGFS) $(LDFLAGS) -o $@ $^ $(LIBRARIES)

lab5.o: lab5.c

clean:
	rm -f lab5 $(OBJECTS)
