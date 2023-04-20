char *source = NULL;
FILE *fp = fopen("foo.txt", "r");

if (fp != NULL) {
	/* Go to the end of the file. */
	if (fseek(fp, 0L, SEEK_END) == 0) {
		/* Get the size of the file. */
		long bufsize = ftell(fp);
		if (bufsize == -1) { /* Error */ }

		/* Allocate our buffer to that size. */
		source = malloc(sizeof char * (bufsize + 1));

		/* Go back to the start of the file. */
		if (fseek(fp, 0L, SEEK_SET) != 0) { /* Error */ }

		/* Read the entire file into memory. */
		size_t newlen = fread(source, sizeof char, bufsize, fp);
		if (ferror(fp) != 0)
			fputs("Error reading file", stderr);
		else
			source[newlen++] = '\0'; /* Just to be safe. */
	}
	fclose(fp);
}

free(source);
