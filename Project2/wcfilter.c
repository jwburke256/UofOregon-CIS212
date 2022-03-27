#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stsplit.h"
#define UNUSED __attribute__((unused))

void countLWC(FILE *fd, long *nl, long *nw, long *nc) {
	char buf[BUFSIZ];
	while (fgets(buf, sizeof buf, fd) != NULL) {
		char **words = stsplit(buf);
		int len;
		len = strlen(buf);
		*nc = *nc + len;
		*nl+=1;
		for (int i = 0; *(words + i) != NULL; i++){
			*nw+=1;
		}
	}
}
int main(UNUSED int argc, UNUSED char *argv[]) {
	int exitStatus = EXIT_SUCCESS;
	long nlines = 0L;
	long nwords = 0L;
	long nchars = 0L;
	countLWC(stdin, &nlines, &nwords, &nchars);
	printf("%8ld%8ld%8ld\n", nlines,nwords,nchars);
	return exitStatus;
}
