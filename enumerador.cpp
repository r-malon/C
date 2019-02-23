#include <iostream>
#include <cstring>
using namespace std;
int main(){
	enum code{ola=10, ole = 15, oli, olo, olu};//padrão: ola=0
	int *foo;
	foo = new int;//memória dinâmica
	foo[0] = 123456;
	foo[1] = 999999999;
	cout << foo[0] << " - " << foo[1] << endl;
	cout << ola << ole << oli; //funciona como uma constante(#define)
}
