#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define UNUSED __attribute__((unused))

int main(UNUSED int argc, UNUSED char *argv[]) {
	long nchars = 0L;
	char buf[BUFSIZ];
	int exitStatus = EXIT_SUCCESS;

	while (fgets(buf, sizeof buf, stdin) != NULL) {
		int len;
		len = strlen(buf);
		nchars = nchars + len;
	}
	printf("%8ld\n", nchars);
	return exitStatus;
}

