#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

void main(){
	char str1[4];
	char str2[4];
	setlocale(LC_ALL, "Portuguese");
	printf("Digite um� frase: ");
	scanf("%s", str1);
	printf("Ag�ra outra: ");
	scanf("%s", str2);
	while (true){
		if (strcmp(str1, str2)!=0){
			printf("Dif�rentes, Digite: ");
			scanf("%s", str1);
			printf("Agora outra: ");
			scanf("%s", str2);
		}
		else{
			printf("S�o iguais!");
			break;
		}
	}
	return 0;
}