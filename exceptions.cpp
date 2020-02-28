#include <iostream>
#include <exception>
using namespace std;

int main(){
	int x;
	cout << "digite: ";
	cin >> x;

	try {
		if (x > 10) {
			throw(80); //lança erro qualquer
		}
		if (x > 20) {
			throw("a");
		}
		cout << "Tudo certo!"; //escreve isso se não der erro
	}
	catch (char let) {
		//if(let == *"a"){
			cout << "Outro erro, maior do que 20";
		//}
	}
	/*catch(...){// (...): erro genérico
		cout << "erro, maior q 10!"; //escreve isso se há erro
	}*/
}/*float divide(float x, float y) {
	int a = 5;
	int b = 8; // \240 error: chars invisiveis ao copiar-e-colar
	try {
		if(y == 0) {
			throw 1;
		}
		else {
			return a/b;
		}
	}
	catch(int erro) {
		if (erro == 1) {
			cout << "Erro de divisao por zero" << endl;
		}
	}
	divide(4, 6);
}*/