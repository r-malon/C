#include <stdio.h>
#include <stdlib.h>

/*
void hack() {
	int *foo;
	while (true) {
		foo = malloc(50000); //bytes
		Sleep(1000);
	}
}
*/

int main() {
	/*
	int x;
	x = fork();
	if (x == 0) {
		hack();
	}
	*/
	//return 0;
	char ble[95];
	scanf("%s", ble);
	system("cls");
	printf("%s copied", ble);
	return 0;
}
