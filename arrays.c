#include <stdio.h>
#include <stdlib.h>

void main() {
	int arr[] = {9, 2, 4, 7, 2, 5, 23};
	int c = 5;
	int a = ++c;
	printf("\nA is %d\n\n", a);

	for (int i = 0; i < (sizeof arr / sizeof *arr); i++) {
		if (i == 2) {
			continue;
		}
		else {
			printf("The %dº item is %d\n", i + 1, arr[i]);
		}
	}
}