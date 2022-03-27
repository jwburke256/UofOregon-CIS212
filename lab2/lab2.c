#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define UNUSED __attribute__((unused))

int main(UNUSED int argc, UNUSED char *argv[]) {
	int returnStatus = EXIT_FAILURE;
	char buf[BUFSIZ];
	while (fgets(buf, BUFSIZ, stdin) != NULL) {
		printf("%s", buf);
	}
	returnStatus = EXIT_SUCCESS;
	return returnStatus;
}

