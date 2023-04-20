#include <iostream>
#include <string>
using namespace std;

template <typename X>
X faz(X a, X b){
	cout << " HEY!!!";
	return a + b;
}

int main() {
	int m = 5, n = 2;
	float i = 3.5, j = 4.5;
	char f[10], g[10];
	cout << "Integer: " << faz(m, n) << endl;
	cout << "Float: " << faz(i, j);
	cout << "String: " << faz(f, g);
}