#include <iostream>
#include <ctime>
#include <clocale>
using namespace std;

int main() {
	setlocale(LC_ALL, ""); // ou setlocale(LC_ALL, "portuguese");
	time_t now = time(0);
	char *data = ctime(&now);
	cout << 'y' << endl; // single-quotes � s� para 1 caracter!
	cout << "\nA 'data'(�orum t�rk��) atual � " << data;
}