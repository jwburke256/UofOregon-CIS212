#include <stdio.h>
#include <stdlib.h>
#include "ADTs/stringADT.h"
#include "ADTs/arraylist.h"
#include <stdbool.h>
#include <unistd.h>

void func(FILE *f, bool upper, bool punct) {
	char c = ' ';
	const ArrayList *al; 
	const String *st = String_create("");
	char buf[BUFSIZ];
	while (fgets(buf, BUFSIZ, f) != NULL) {
		st->clear(st);
		st->append(st, buf);
		if (upper) {
			st->lower(st); // makes lowercase
		}
		if (punct) {
			st->translate(st,"[:punct:]", c); //converts punctuation to white space
		}
		al = st->split(st, ""); //split up into words
		if (al != NULL) {
		const Iterator *it = al->itCreate(al);
			while (it->hasNext(it)) {
				char *temp;
				(void) it->next(it, (void **)&temp); //what dis do?
				printf("%s\n", temp);
			}
			it->destroy(it);
			al->destroy(al);  //frees up mem from ADTs
		}
	}
	st->destroy(st);
}	

int main(int argc, char *argv[]) {
	int opt;
	bool upperCase = false; //uppercase option
	bool punctuation = false; //punctuation option
	extern int opterr;
	int exitStatus = EXIT_FAILURE;

	opterr = 0;
	while ((opt = getopt(argc, argv, "lp")) != -1) {
		switch(opt) {
			case 'l': upperCase=true; break;
			case 'p': punctuation=true; break;
			default:
				  fprintf(stderr, "%s: invalid option -%c\n", argv[0], optopt);
				  goto cleanup;
		}
	}
	int nFiles = argc - optind;
	if (nFiles == 0) {
		func(stdin, upperCase, punctuation); //get standard input
	} else {
		int i;
		for (i = optind; i < nFiles + optind; i++) {
			FILE *f = fopen(argv[i], "r"); //open file in read mode
			if (f == NULL) {
				fprintf(stderr, "Unable to open file %s\n", argv[i]);
				goto cleanup;
			}
			func(f, upperCase, punctuation);
			fclose(f);
		}
		exitStatus = EXIT_SUCCESS;
	}

	cleanup:

	return exitStatus;
}







