#include <stdio.h>
#include <stdlib.h>
void main(){
	int lista[] = {9, 2, 4, 7, 2, 5, 23};
	int i;
	int c = 5;
	int a = ++c;
	printf("\nA igual %d\n\n", a);
	for (i = 0; i < (sizeof lista/sizeof *lista); i++){
		if (i == 2){
			continue;
		}
		else{
			printf("o %d da lista eh %d\n", i+1, lista[i]);	
		}
	}
}
