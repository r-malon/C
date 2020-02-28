#include <iostream>
//#include <new>
using namespace std;

int main() {
	int *foo = new (nothrow)int;
	int z;
	//int *xaxa = new int[10]; //aloca 10 ints não iniciados
	//char *bla = new char;
	cout << "Diga o tamanho da lista: ";
	cin >> z;
	for (int i = 0; i < z; i++) {
		cout << "Digite: ";
		cin >> *foo;
		cout << *foo << endl;
	}
	//cout << bla;
	delete[] foo; //limpa memória em todos itens do array
	//delete foo limpa somente o #1 elemento do array
}