#include <iostream>
#include <cstring>
#include <locale>
using namespace std;

/*#ifdef __cplusplus
#error trolei, c++ negado!
#error blabla
#endif*/
struct obj {
	char name[];
	float price;
};

int main() {
	setlocale(LC_ALL, "Portuguese");
	cout << "Compilação inîciada no dia " << __DATE__ << endl;
	struct obj cadeira;
	int x = 23243543;
	//int list[] = {43, 69, {12, 67, 45}, 654}; //sublist
	char y[] = "yprueeghtyqeeebgfydugfsydufhdujhndhnnhdfnsiuhviiurihcueiwrurifbsdiyidyyncvm";
	int oco = 15.87;
	float a = 2;
	int list[] = {3, 5, 6, 77};
	bool verd = 0;
	list[8] = 60;
	//typedef int inteiro --> muda nome do tipo de dado
	int& ref = x; //referencia

	switch(oco) {
		case 40:
			cout << "bla" << endl;
			break;
		case 15:
			cout << "numero certo" << endl;
			break;
		default:
			cout << "padrao" << endl;// ñ aparece devido aos 'break's
			break;
	}
	printf("print it!!!"); //scanf tbm é válido
	cout << strlen(y) << endl;
	cout << "refrencia: " << ref << endl;
	cout << sizeof(x) << sizeof(y) << "ola verdade" << sizeof(verd) << sizeof(oco) << sizeof(a) << endl;
	cerr << "erros\n"; //inútil em coisas simples
	clog << "erro de logs!\n\n"; //idem
	strcpy(cadeira.name, " ola bartaeronomics ");
	cadeira.price = 45.59;
	cout << cadeira.name << " custa " << cadeira.price << endl << endl;
	cout << list;
}