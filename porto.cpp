#include <iostream>
using namespace std;

int main() {
	int total;
	int x;
	do {
		cout << "Diga quantos conteiners serão carregados: ";
		cin >> x;
		while (x > 50) {
			cout << "Não cabe no navio, diga novamente: ";
			cin >> x;
		}
		if (x == 50) {
			cout << "NAVIO CARREGADO!!!";
			break;
		}
		else {
			total += x;
		}
	}
	while (total <= 50);
}