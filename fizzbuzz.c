#include <stdio.h>
#include <stdbool.h>

int
main(int argc, char const *argv[])
{
	int n, i;
	int fizz, buzz;
	bool modfizz, modbuzz;

	if (argc < 2) {
		fputs("Enter Fizz: ", stdout);
		scanf("%d", &fizz);
		fputs("Enter Buzz: ", stdout);
		scanf("%d", &buzz);
		fputs("Enter how many times you want to FizzBuzz: ", stdout);
		scanf("%d", &n);
	} else {}
	for (i = 1; i <= n; ++i) {
		modfizz = !(i % fizz), modbuzz = !(i % buzz);
		if (modfizz || modbuzz) {
			if (modfizz)
				fputs("Fizz", stdout);
			if (modbuzz)
				fputs("Buzz", stdout);
		} else {
			printf("%d", i);
		}
		putchar('\n');
	}
	return 0;
}
