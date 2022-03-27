#include <stdio.h>
#include <stdlib.h>
#include "stsplit.h"
#define UNUSED __attribute__((unused))

int main(UNUSED int argc, UNUSED char *argv[]) {
	long nwords = 0L;
	char buf[BUFSIZ];
	int exitStatus = EXIT_SUCCESS;

	while (fgets(buf, sizeof buf, stdin) != NULL) {
		char **words = stsplit(buf);
		for (int i = 0; *(words + i) != NULL; i++){	
			nwords++;
		}
	}
	printf("%8ld\n", nwords);
	return exitStatus;
}

