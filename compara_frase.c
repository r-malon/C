#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <locale.h>

int main() {
	char str1[4], str2[4];
	char* str = "Hello Amazing World!";
	setlocale(LC_ALL, "Portuguese");
	printf("Digite um� frase: ");
	scanf("%s", str1);
	printf("Ag�ra outra: ");
	scanf("%s", str2);
	printf("%s\n", str);

	while (true) {
		if (strcmp(str1, str2) != 0) {
			printf("Dif�rentes, digite: ");
			scanf("%s", str1);
			printf("Agora outra: ");
			scanf("%s", str2);
		}
		else {
			printf("S�o iguais!");
			break;
		}
	}
	return 0;
}
