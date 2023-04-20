#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int
clamp(int d, int min, int max)
{
	int const t = d < min ? min : d;
	return t > max ? max : t;
}

int
main(int argc, char const *argv[])
{
	srand(time(0));
}
