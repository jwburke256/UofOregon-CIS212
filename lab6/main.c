#define _GNU_SOURCE
#include "ADTs/iterator.h"
#include "studentlist.h"
#include "student.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// Macros - Predifned messages for output
#define USAGE "usage: ./%s [-f FILE]\n"
#define ERR1 "%s: invalid option '-%c'\n"
#define ERR2 "%s: unable to open file: %s\n"


// Function to process input from the file.
void procFile(FILE *fd) {
	Student *st = NULL;
	const StudentList *lst = StudentList_create(0L, (void *) freeStudent);
	while ((st = getStudent(fd)) != NULL) { 
		(void) lst->append(lst, st);
	}

	const Iterator *it = lst->itCreate(lst);
	while(it->hasNext(it)) {
		Student *temp;
		(void) it->next(it, (void **)&temp);
		printStudent(stdout, temp);
	}
	it->destroy(it);
	lst->destroy(lst);
}


int main(int argc, char *argv[]) {
	int opt;
	char *filename;
	bool ifF = false;
	extern int opterr;
	int exitStatus = EXIT_FAILURE;

	opterr = 0;
	while((opt = getopt(argc, argv, "f:")) != -1) {
		switch(opt) {
			case 'f': ifF = true; filename = optarg; break;
			default:
				fprintf(stderr, ERR1, argv[0], optopt);
				fprintf(stderr, USAGE, argv[0]);
				goto cleanup;
		}
	}
	
	if((argc != optind)) {
		fprintf(stderr, USAGE, argv[0]);
		exitStatus = EXIT_FAILURE;
	} else if(!ifF) {
		procFile(stdin);
		exitStatus = EXIT_SUCCESS;
	} else if(ifF){
		FILE *fd = fopen(filename, "r");
		if(fd == NULL) {
			fprintf(stderr, ERR2, argv[0], filename);
			exitStatus = EXIT_FAILURE;
		} else {
			procFile(fd);
			fclose(fd);
			exitStatus = EXIT_SUCCESS;
		}
	}
	cleanup:
	return exitStatus;
}
