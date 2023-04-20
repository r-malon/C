/*
cat - concatenate and print files
usage: cat [-u] [file...]
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void
cat(FILE *fp) {
	static char buf[4096];
	size_t n;
	while ((n = fread(buf, sizeof (char), sizeof buf, fp)) > 0)
		if (fwrite(buf, sizeof (char), n, stdout) != n)
			perror("Write error");
}

int
main(int argc, char *argv[])
{
	FILE *fp;

	if (strcmp(argv[1], "-u") == 0) {
		setbuf(stdout, NULL);
		++argv; --argc;
	}

	if (argc == 1) {
		fp = stdin;
		cat(fp);
	} else while (*++argv) {
		if (**argv == '-') {
			fp = stdin;
		} else {
			fp = fopen(*argv, "r");
			if (fp == NULL) {
				fprintf(stderr, "Could not open file '%s'.\n", *argv);
				continue;
			}
		}
		cat(fp);
		if (fp != stdin)
			fclose(fp);
	}

	return 0;
}
