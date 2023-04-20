#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <getopt.h>
/*
char *
itoh(int x) {
	char *hex = "0123456789ABCDEF";
	char *s;
	int tmp;
	for (int i = 0; i < sizeof(x)*CHAR_BIT; ++i) {
		
	}
	return ;
}
*/
int
main(int argc, char *argv[])
{
	int c;
	FILE *fp;

	if (argc > 1) {
		fp = fopen(argv[1], "r");
		if (fp == NULL) {
			fprintf(stderr, "Could not open file '%s'.\n", argv[1]);
			return EXIT_FAILURE;
		}
	} else {
		fp = stdin;
	}

	while ((c = getc(fp)) != EOF) {
		printf("%X", c);
	}

	if (argc > 1)
		fclose(fp); /* undefined behavior if stdin */

	return 0;
}
