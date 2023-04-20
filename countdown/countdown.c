#define _POSIX_C_SOURCE 200809L

#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/* countdown: count down seconds from the number specified in argv[1]. */
int
main(int argc, char *argv[])
{
	char *ep;
	unsigned long seconds;
	if (argc != 2) {
		fprintf(stderr, "%s\n", "pass exactly one argument");
		exit(1);
	}
	seconds = strtoul(argv[1], &ep, 10);
	if (*argv[1] == '\0' || *ep != '\0') {
		fprintf(stderr, "%s\n", "argument is not a number");
		exit(1);
	}
	if (errno == ERANGE && (seconds == ULONG_MAX || seconds > UINT_MAX)) {
		fprintf(stderr, "%s\n", "argument out of range");
		exit(1);
	}

	/* There are at least 3 bugs in this loop. What are they? */
	for (; seconds; seconds--) {
		if (printf("%lu\n", seconds) < 0) {
			perror(NULL);
			exit(1);
		}
		sleep(1);
	}
	exit(0);
}
