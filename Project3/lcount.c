#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define UNUSED __attribute__((unused))

int main(UNUSED int argc, UNUSED char *argv[]) {
	char buf[BUFSIZ];
	char last[BUFSIZ];
	int exitStatus = EXIT_SUCCESS;
	fgets(last, sizeof last, stdin);
	long ncount = 1L;

	while (fgets(buf, sizeof buf, stdin) != NULL) {
		if (strcmp(buf, last) != 0) {
			printf("%7ld %s", ncount, last);
			strcpy(last, buf);
			ncount = 1L;
		}
		else
			ncount++;
	}
	return exitStatus;
}

