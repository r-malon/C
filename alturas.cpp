#include <iostream>
#include <cstring>
#include <locale>
using namespace std;
int const eternal = 10;
//eternal = 24 --> vari�vel imut�vel (read-only)

int main() {
	setlocale(LC_ALL, "");
	int y = 28ul;
	int n;
	long double x;
	/*int z = 80;
	z = 98; mudar vari�vel*/
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
		cout << "A " << i + 1 << "* altura � " << list[i] << endl;
		soma += list[i];
		//&list[i] para ver endere�o na mem�ria
	}
	cout << "A m�dia de alturas � " << soma / n;
	//cout << " as alturas s�o " << list;
	return 0;
}
