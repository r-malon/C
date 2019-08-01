#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Carro {
	int custo;
	char marca[20];
	char cor[20];
};

int main(){
	struct Carro Gol;
	char cor2[20];
	char marca2[20];
	int custo2;
	printf("Marca do carro: ");
	scanf("%s", marca2);
	printf("Digite a cor: ");
	scanf("%s", cor2);
	printf("Digite o preço: ");
	scanf("%i", custo2);
	strcpy(Gol.marca, marca2);
	strcpy(Gol.cor, cor2);
	Gol.custo = custo2;
	printf("Um %s de cor %s custa %d dólares!", Gol.marca, Gol.cor, &Gol.custo);
	return 0;
}
