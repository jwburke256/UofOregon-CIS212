#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[]) {
	int opt;
	bool opti, optd, optu, optc;
	int exitStatus = EXIT_SUCCESS;
	char *filename;

	opti = optd = optu = optc = false;
	opterr = 0;
	while ((opt = getopt(argc, argv, "iduc")) != -1) {
		switch(opt) {
			case 'i': opti = true; break;
			case 'd': optd = true; break;
			case 'u': optu = true; break;
			case 'c': optc = true; break;
			default: printf("Error, unrecognized option %d\n", optopt);
		}
	}
	if (opti)
		printf("Checking case insensitive\n");
	if (optc)
		printf("Print line count\n");
	if (optd && optu)
		printf("Printing nothing\n");
	else {
		if (optd)
			printf("Checking duplicate lines\n");
		if (optu)
			printf("Checking uniq lines\n");
	}
	if (argc > optind) {
		filename = argv[optind];
		printf("Opening File %s", filename);
	}
	return exitStatus;
}
