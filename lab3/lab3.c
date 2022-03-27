#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>

void prefixCat(FILE *fd, bool ifI, bool ifF) {
	int i=0;
	char line[BUFSIZ];
	char prefix[50] = "";

	if (!ifF) {
		printf(">>> ");
	}

	while (fgets(line, BUFSIZ, fd) != NULL) {
		if (strcmp("1\n", line) == 0) {
			break;
		} else {
			       if (ifI) {
				       sprintf(prefix, "%4d: ", i);
				       i++;
				      }
			       printf("%s%s\n", prefix, line);
			    }
		if (!ifF) {
			printf(">>> ");
		}
	}
	printf("Goodbye!\n");
}

int main(int argc, char *argv[]) {
	int option;
	extern int opterr;
	bool ifI, ifF;	//If interactive, and if File
	bool start = true;
	int returnStatus = EXIT_FAILURE;
	char *filename;

	opterr = 0;
	ifI = ifF = false;
	while ((option = getopt(argc, argv, "f:i")) != -1) {
		switch(option) {
			case 'i': ifI = true; break;
			case 'f': ifF = true; filename = optarg; break;
			default:
				  printf("Unkown flag: -%c\n", optopt);
				  start = false;
				  break;
		}
	}
	if(start) {
		if (ifF) {
			FILE *fd = fopen(filename, "r");
			if (fd == NULL) {
				fprintf(stderr, "cannot open file %s\n", filename);
							returnStatus = EXIT_FAILURE;
							} else {
							prefixCat(fd, ifI, ifF);
							fclose(fd);
						}
					} else {
					prefixCat(stdin, ifI, ifF);
					}
					returnStatus = EXIT_SUCCESS;
				}
	return returnStatus;
}
