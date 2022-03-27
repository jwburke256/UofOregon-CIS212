CFLAGS=-W -Wall
PROGRAMS=lstrip lcase lcount suniqargs suniq

all: $(PROGRAMS)

lstrip: lstrip.o
	gcc -o $@ $^

lcase: lcase.o
	gcc -o $@ $^

lcount: lcount.o
	gcc -o $@ $^

suniqargs: suniqargs.o
	gcc -o $@ $^

suniq: suniq.o
	gcc -o $@ $^

lstrip.o: lstrip.c
lcase.o: lcase.c
lcount.o: lcount.c
suniqargs.o: suniqargs.c
suniq.o: suniq.c

clean:
