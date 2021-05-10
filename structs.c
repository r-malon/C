#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Car {
	double cost;
	char brand[20];
	char color[20];
};

int main() {
	struct Car Gol;
	char color2[20], brand2[20];
	double cost2;
	printf("Brand: ");
	scanf("%s", brand2);
	printf("Color: ");
	scanf("%s", color2);
	printf("Price: ");
	scanf("%i", cost2);
	strcpy(Gol.brand, brand2);
	strcpy(Gol.color, color2);
	Gol.cost = cost2;
	printf("A %s-colored %s costs %d dollars!", Gol.color, Gol.brand, &Gol.cost);
	return 0;
}
