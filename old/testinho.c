#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#define PIA 3

void main() {
	int x, valores;
	char nome[10];
	printf("Digite seu nome: ");
	scanf("%s", nome);
	MessageBox(0, "Venha relaxar %s!!!", "Jailson diz...", 1);
	printf("Agora um numero: ");
	scanf("%i", &x);
	valores = x * PIA;
	printf("O valor vezes 3 eh %i", valores);
	int num = 75;
	unsigned int ble;
	char var[10];
	printf("\nO num eh %i \n", x);
	printf("Digite sua idade: ");
	scanf("%i", &ble);
	printf("Agora uma frase: ");
	scanf("%s", var);
	int i;

	if ( ble >= 20 ) {
		printf("O numero %i eh maior que 20, tal como %s\n", ble, var);
	}
	else if (ble >= 12 && ble <= 15) {
		printf("Bla!, %s", var);
	}
	else {
		printf("%i menor q 20", ble);	
	}
	for (i = 0; i < x + 1; i++) {
		printf("Agora eh %i bla\n", i);
	}

	int var1 = 10;
	int var2 = 5;
	int c = somar(var1, var2);
	/*int d = multi(var1, var2);*/
	printf("O resultado eh %i e tambem %i", c);
	/*return 0;*/
};
/*void multi(int var1, int var2){
	printf("ola: ");
	return var1 * var2;
}*/
int somar(int var1, int var2) {
	printf("Vamos somar %i com %i", var1, var2);
	return var1 + var2;
};