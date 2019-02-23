#include <iostream>
#include <cstring>
#include <clocale>
using namespace std;
using c = char; //EQUIVALENTE a TYPEDEF
using x = char[10];

union hah{ //ocupam mesmo espaço na memória
	char u1[];
	int u2 = 27;
	int u3;
}uni;

int main(){
	setlocale(LC_ALL, ""); //acentos ocupam espaço tbm!
	SIGABRT;
	c frase;
	uni.u3 = 98; //u1 e u2 tbm são 98, ocupam mesmo lugar na memória
	cout << uni.u3 << uni.u2 << " xaxaxa, ";
	cout << "bla: ";
	cin >> frase;
	cout << frase;
}
/*float divide(float x, float y) { //exemplo
    try {
        if(y == 0) {
            throw 1;
        } else {
            return a/b;
        }
    } catch(int erro) {
        if (erro == 1) {
            cout << "Erro de divisao por zero" << endl;
        }
    }
}*/