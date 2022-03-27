#include <stdio.h>
#include <stdlib.h>
#include "ADTs/stringADT.h"
#include "ADTs/arraylist.h"
#include <stdbool.h>
#include <unistd.h>
#include <math.h>

#define USAGE "usage: %s [-p] [FILE] ...\n"

void func(FILE *f) {
	int i;
	const ArrayList *csv = ArrayList_create(0L, NULL);
	const String *st = String_create("");
	char buf[BUFSIZ];
	while (fgets(buf, BUFSIZ, f) != NULL) {
		st->clear(st);
		st->append(st, buf); //buf = "1,2,3" -->["1", "2", "3"]
		const ArrayList *al = st->split(st, ",");
		const Iterator *it = al->itCreate(al);
		printf("Looping using iterator\n");
		while (it->hasNext(it)) {
			char *temp;
			(void) it->next(it, (void **)&temp);
			printf("|%d|\n", atoi(temp));
		}
		printf("\nLooping using indexing\n");
		for (i=0; i<al->size(al); i++) {
			char *temp;
			(void) al->get(al, i, (void**)&temp);
			printf("|%d|\n", atoi(temp));
		}
		al->destroy(al);
		it->destroy(it); //frees up adt memory
	}
	st->destroy(st);
	csv->destroy(csv);

}

int main(int argc, char *argv[]) {
	int opt;
	int nFiles = 0;
	FILE *fd[50];
	bool printFile = false; //option for our program
	extern int opterr;
	int exitStatus = EXIT_FAILURE;

	opterr = 0;
	while ((opt = getopt(argc, argv, "p")) != -1) {
		switch(opt) {
			case 'p': printFile=true; break;
			default:
				  fprintf(stderr, "%s: invalid option -%c\n", argv[0], optopt);
				  fprintf(stderr, USAGE, argv[0]);
				  goto cleanup;
		}
	}

	if ((argc-optind) == 0) {
		fprintf(stderr, USAGE, argv[0]);
		goto cleanup;
	} else {
		int i;
		for (i = optind; i < argc; i++) {
			FILE *f = fopen(argv[i], "r");
			if (f == NULL) {
				fprintf(stderr, "Unable to open file %s\n", argv[i]);
				goto cleanup;
			}
			fd[nFiles++] = f;
		}
		if (printFile) {
			for (i = 0; i < nFiles; i++) {
				func(fd[i]);
				}
		}
		exitStatus = EXIT_SUCCESS;
	}


	cleanup:
		for (int i=0; i<nFiles; i++) {
			fclose(fd[i]);
		}

	return exitStatus;
}
