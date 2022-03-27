#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define UNUSED __attribute__((unused))

int main(UNUSED int argc, UNUSED char *argv[]) {
	char buf[BUFSIZ];
	char last[BUFSIZ];
	int exitStatus = EXIT_SUCCESS;
	fgets(last, sizeof last, stdin);

	while (fgets(buf, sizeof buf, stdin) != NULL) {
		if (strcmp(buf, last) != 0) {
			printf(last);
			strcpy(last, buf);
		}
	}
	return exitStatus;
}

