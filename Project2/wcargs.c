#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[]) {
	int opt;
	bool printl, printw, printc;
	int exitStatus = EXIT_SUCCESS;

	printl = printw = printc = false;
	opterr = 0;
	while ((opt = getopt(argc, argv, "lwc")) != -1) {
		switch(opt) {
			case 'l': printl = true; break;
			case 'w': printw = true; break;
			case 'c': printc = true; break;
		}
	}
	if (printl == printw && printw == printc && printc == false)
		printl = printw = printc = true;
	if (printl == true)
		printf("Counting lines\n");
	if (printw == true)
		printf("Counting words\n");
	if (printc == true)
		printf("Counting characters\n");
	int nfiles = argc - optind;
	if (nfiles == 0)
		printf("Processing standard input and no total line\n");
	char *filenames[nfiles];

	for (int i = 0; i <nfiles; i++)
	{
		filenames[i] = argv[optind + i];
	}
	if (nfiles != 0)
	{
		if (nfiles == 1)
			printf("Processing %s and no total line\n", filenames[0]);
		else
		{
			printf("Processing ");
			for (int i = 0; i <nfiles; i++)
			{
				if (i != 0)
					printf(", %s", filenames[i]);
				else
					printf("%s", filenames[0]);	
			printf(" and a total line\n");
		}
	}
	return exitStatus;
}

