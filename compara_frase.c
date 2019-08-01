#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

void main(){
	char str1[4];
	char str2[4];
	setlocale(LC_ALL, "Portuguese");
	printf("Digite umà frase: ");
	scanf("%s", str1);
	printf("Agôra outra: ");
	scanf("%s", str2);
	while (true){
		if (strcmp(str1, str2)!=0){
			printf("Diférentes, Digite: ");
			scanf("%s", str1);
			printf("Agora outra: ");
			scanf("%s", str2);
		}
		else{
			printf("São iguais!");
			break;
		}
	}
	return 0;
}