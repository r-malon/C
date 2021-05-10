#include <stdio.h>
#include <stdbool.h>

int
main(int argc, char const *argv[])
{
	int n, i;
	int fizz, buzz;
	bool modfizz, modbuzz;

	printf("Enter Fizz: ");
	scanf("%d", &fizz);
	printf("Enter Buzz: ");
	scanf("%d", &buzz);
	printf("Enter how many times you want to FizzBuzz: ");
	scanf("%d", &n);

	for (i = 1; i <= n; ++i) {
		modfizz = !(i % fizz), modbuzz = !(i % buzz);
		if (modfizz || modbuzz) {
			if (modfizz)
				printf("Fizz");
			if (modbuzz)
				printf("Buzz");
		} else {
			printf("%d", i);
		}
		printf("\n");
	}
	return 0;
}
