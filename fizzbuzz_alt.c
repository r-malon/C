#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
	int n, i;
	if (argc < 2) n = 100;
	else n = atoi(argv[1]);

	for (i = 1; i <= n; i++) {
		if ((i % 3 || i % 5) == 0)
			printf("%d FizzBuzz\n", i);
		else if (i % 3 == 0)
			printf("%d Fizz\n", i);
		else if (i % 5 == 0)
			printf("%d Buzz\n", i);
		else
			printf("%d\n", i);
	}
	return 0;
}
