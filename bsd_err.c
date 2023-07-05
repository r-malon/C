#if defined(BSD)
	#include <err.h>
#else
/* Adapted from NetBSD implementation */
/* https://nxr.netbsd.org/xref/src/lib/libc/gen/err.c */
void
err(int eval, const char *fmt, ...)
{
	va_list ap;

	va_start(ap, fmt);
	fprintf(stderr, "%s: ", argv[0]);
	if (fmt != NULL) {
		vfprintf(stderr, fmt, ap);
		fprintf(stderr, ": ");
	}
	fprintf(stderr, "%s\n", strerror(errno));
	va_end(ap);
	exit(eval);
}

void
warn(const char *fmt, ...)
{
	va_list ap;

	va_start(ap, fmt);
	fprintf(stderr, "%s: ", argv[0]);
	if (fmt != NULL) {
		vfprintf(stderr, fmt, ap);
		fprintf(stderr, ": ");
	}
	fprintf(stderr, "%s\n", strerror(errno));
	va_end(ap);
}
#endif
