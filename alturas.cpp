#include <iostream>
#include <cstring>
#include <locale>
using namespace std;
int const eterna = 10;
//eterna = 24 --> vari�vel imut�vel(read-only)
int main(void){
	setlocale(LC_ALL, "");
	int y = 28ul;
	long int n;
	long double x;
	long int i;
	/*int z = 80;
	z = 98; mudar vari�vel*/
	cout << "long int: " << y << endl;
	cout << "Digite qnts alturas vai medir: ";
	cin >> n;
	int lis[n];
	float soma;
	for(i=0;i<n;i++){
		cout << "Digite a altura: ";
		cin >> x;
		lis[i] = x;
	}
	for(i=0; i<n; i++){
		cout << "A " << i+1 << "* altura eh " << lis[i] << endl;
		soma += lis[i];
		//&lis[i] para ver endere�o na mem�ria	
	}
	cout << "A m�dia de alturas � " << soma/n;
	//cout << " as alturas s�o " << lis;
}
