#include <iostream>
#include <cstring>
#include <clocale>
using namespace std;
int gl = 89; //global

// &: endereço da variável; *: conteúdo do endereço

int main() {
	setlocale(LC_ALL, "");
	char oi[] = "0lap3s5oas";
	float ola = 17;
	int num, x;
	int nab = 2;
	char bla[20];
	int gl = 15; //local
	int arr[] = {5, 6, 7, 8, 2, 9, 4, 3, 65, 23, 2145};
	int arrlen = sizeof(arr) / sizeof(int); /* int tem 4 bits, 4*11 itens = 44 bytes */
	::gl++; //global
	gl--;  //local
	cout << "global: " << ::gl << "  local: " << gl << endl;
	cout << endl << oi << endl << endl;
	cout << sizeof(arr) << " tamanho da lista em bytes e tamanho de int é " << sizeof(int) << endl;
	cout << "Digite uma frase: ";
	cin.getline(bla, 20);
	cout << "Tamanho de " << bla << " é " << strlen(bla) << endl;
	cout << "Agora é diferente!\n\n";
	for(int x = 0; x < arrlen; x++) {
		cout << "O " << x + 1 << "* elemento da lista é " << arr[x] << endl;
	}
	/*LOOP:do{
		if (num == 3) {
			cout << num;
			num = num + 2;
			goto LOOP;
		}
	}
	while(num < 30);*/
	//system("pause"); --> (geralmente) inútil!!!
	return 0;
}
