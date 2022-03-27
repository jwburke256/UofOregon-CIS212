#include "ADTs/stack.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define UNUSED __attribute__((unused))

void isPalindrome(FILE *fd, const Stack *st) {
	char buf[BUFSIZ];
	while (fgets(buf, BUFSIZ, fd) != NULL) {
		int mid, i, N = strlen(buf);
		bool isPalin = true;
		if (buf[N-1] == '\n') { buf[--N] = '\0'; }
		st->clear(st);
		mid = N/2;
		for (i=0; i<mid; i++) {
			st->push(st, ADT_VALUE((long)buf[i]));
		}
		if ((N%2) == 1) { mid++; }
		for (i=mid; i<N; i++) {
			long value;
			st->pop(st, ADT_ADDRESS(&value));
			if ((char)value != buf[i]) {
				isPalin = false;
				break;
			}
		}
		printf("%s is a palindrome: %s\n",buf, (isPalin) ? "true" : "false");
	}
}



int main(UNUSED int argc, UNUSED char *argv[]) {
	int exitStatus = EXIT_FAILURE;
	const Stack *st = Stack_create(doNothing);
	if (st == NULL) {
		fprintf(stderr, "Unable to malloc Stack\n");
		goto exit;
	} else {
		isPalindrome(stdin, st);
		st->destroy(st);
		exitStatus = EXIT_SUCCESS;
	}
	exit:
	return exitStatus;

}