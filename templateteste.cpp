#include <iostream>
#include <string>
using namespace std;

template <typename X>
X faz(X a, X b){
	cout << " HEY!!! ";
	return a + b;
}

int main(){
	int q = 5, w = 2;
	float i = 3.5, j = 4.5;
	char f[10], g[10];
	cout << "intero: " << faz(q, w) << endl;
	cout << "flutunte: " << faz(i, j);
	cout << "strings: " << faz(f, g);
}
