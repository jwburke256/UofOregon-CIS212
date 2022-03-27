#include "stringlist.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define UNUSED __attribute__((unused))

//Function to process input from file/stdinput
StringList* procFile(FILE *fd) {
	char buf[BUFSIZ];
	StringList *sl = (StringList*) StringList_create(0L);
	while ((fgets(buf, BUFSIZ, fd)) != NULL) {
		if (!(sl->append(sl, buf))) {
			fprintf(stderr, "Unable to append to StringList");
		}
	}
	return sl;
}

void reverse(StringList *sl) {
	long size = sl->size(sl);
	for (long i = size-1; i >= 0L; i--) {
		char *temp;
		sl->get(sl, i, &temp);
		printf("%s", temp);
	}
}



int main(UNUSED int argc, UNUSED char *argv[]) {
	int exit_status = EXIT_FAILURE;
	StringList* sl = procFile(stdin);
	reverse(sl);
	sl->destroy(sl);
	exit_status = EXIT_SUCCESS;
	return exit_status;
}