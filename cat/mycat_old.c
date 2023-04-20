#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void
dump(FILE *fp) {
	int c;
	while ((c = getc(fp)) != EOF)
		putchar(c);
}

int
main(int argc, char *argv[])
{
	int i = 1;
	FILE *fp;

	if (argc <= 1) {
		fp = stdin;
		dump(fp);
		goto exit;
	}

	do {
		if (!strcmp(argv[i], "-")) {
			fp = stdin;
		} else {
			fp = fopen(argv[i], "r");
			if (fp == NULL) {
				fprintf(stderr, "Could not open file '%s'.\n", argv[i]);
				return EXIT_FAILURE;
			}
		}
		dump(fp);
	} while (++i < argc);

	exit:
	if (argc > 1)
		fclose(fp);

	return 0;
}
