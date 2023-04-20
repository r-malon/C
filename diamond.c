#include <stdio.h>
#include <stdlib.h>

#define N 11
#define C '*'

int
main(int argc, char const *argv[])
{
	int space, ch, flag, n, c, i, j;
	n = N; c = C;
	switch (argc) {
	case 3: c = argv[2][0]; /* FALLTHROUGH */
	case 2: n = atoi(argv[1]); break;
	default: break;
	}
	flag = (n&1) + 1;
	space = n / 2;
	ch = (n&1) ? 1 : 2;

	/* Not working for even 'n' */
	for (i = 0; i < n * flag; i += flag) {
		for (j = 0; j < space; ++j)
			putchar(' ');
		for (j = 0; j < ch; ++j)
			putchar(c);
		putchar('\n');
		i < n - flag ? (ch += flag) : (ch -= flag);
		i > n - flag ? space++ : space--;
	}
	return 0;
}
