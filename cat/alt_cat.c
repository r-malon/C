#include <unistd.h>

void
cat(FILE *fp) {
	char buf[4096];
	size_t n;
	int f = fileno(fp);
	while ((n = read(f, buf, sizeof buf)) > 0)
		if (write(STDOUT_FILENO, buf, n) != n)
			perror("Write error");
}
