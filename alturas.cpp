#include <iostream>
#include <cstring>
#include <locale>
using namespace std;
int const eternal = 10;
//eternal = 24 --> variável imutável (read-only)

int main() {
	setlocale(LC_ALL, "");
	int y = 28ul;
	int n;
	long double x;
	/*int z = 80;
	z = 98; mudar variável*/
	cout << "long int: " << y << endl;
	cout << "Digite quantas alturas vai medir: ";
	cin >> n;
	long double list[n];
	float soma;

	for (int i = 0; i < n; i++) {
		cout << "Digite a altura: ";
		cin >> x;
		list[i] = x;
	}
	for (int i = 0; i < n; i++) {
		cout << "A " << i + 1 << "* altura é " << list[i] << endl;
		soma += list[i];
		//&list[i] para ver endereço na memória
	}
	cout << "A média de alturas é " << soma / n;
	//cout << " as alturas são " << list;
	return 0;
}
