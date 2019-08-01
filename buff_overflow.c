#include <stdio.h>
#include <stdlib.h>

/*void hack(){
	int *foo;
	while(1){
		foo=malloc(50000); //bytes
		Sleep(1000);
	}
}*/

int main(){
	/*	int x;
	x=fork(); //cria outro processo; EXCLUSIVO PARA LINUX
	if(x==0){
		hack();
	}*/
	//return 0;
	char ble[95];
	scanf("%s",ble);
	system("cls");
	printf("%s copiado", ble);
	return 0;
}
