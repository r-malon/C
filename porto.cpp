#include <iostream>
using namespace std;
int main(){
	int total;
	int x;
	do{
		cout << "diga qnts conteiners vai carregar: ";
		cin >> x;
		while(x > 50){
			cout << "nao cabe no navio, diga dnovo: ";
			cin >> x;
		}
		if(x==50){
			cout << "NAVIO CARREGADO!!!";
			break;
		}
		else{
			total += x;
		}
	}
	while(total<=50);
}
