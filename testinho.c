#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#define PIA 3

void main(){
	int x, valores;
	char nome[10];
	printf("digite seu nome: ");
	scanf("%s", nome);
	MessageBox(0, "Vem relaxar %s!!!", "Jailson diz...", 1);
	printf("agora um numero: ");
	scanf("%i", &x);
	valores = x * PIA;
	printf("o valor vexes 3 eh %i", valores);
	int num = 75;
	unsigned int ble;
	char var[10];
	printf("\no num eh %i \n", x);
	printf("digite sua idade: ");
	scanf("%i", &ble);
	printf("agora uma bela frase: ");
	scanf("%s", var);
	int i;
	if ( ble >= 20 ){
		printf("o numero %i eh maior que 20, tal como %s\n", ble, var);
	}
	else if (ble >= 12 && ble <= 15){
		printf("mophobics!, %s", var);
	}
	else{
		printf("ola... %i menor q 20", ble);	
	}
	for (i = 0; i < x+1; i++){
		printf("agora eh o %i bla\n", i);
	}
	int var1 = 10;
	int var2 = 5;
	int c = somar(var1, var2);
	/*int d = multi(var1, var2);*/
	printf("o resultado eh %i e tbm %i", c);
	/*return 0;*/
};
/*void multi(int var1, int var2){
	printf("ola: ");
	return var1 * var2;
}*/
int somar(int var1, int var2){
	printf("vamos somar %i com %i", var1, var2);
	return var1 + var2;
};