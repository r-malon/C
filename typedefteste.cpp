#include <iostream>
#include <cstring>
#include <clocale>
using namespace std;
using c = char; //EQUIVALENTE a TYPEDEF
using x = char[10];

union hah{ //ocupam mesmo espa�o na mem�ria
	char u1[];
	int u2 = 27;
	int u3;
}uni;

int main(){
	setlocale(LC_ALL, ""); //acentos ocupam espa�o tbm!
	SIGABRT;
	c frase;
	uni.u3 = 98; //u1 e u2 tbm s�o 98, ocupam mesmo lugar na mem�ria
	cout << uni.u3 << uni.u2 << " xaxaxa, ";
	cout << "bla: ";
	cin >> frase;
	cout << frase;
}
/*float divide(float x, float y) { //exemplo
����try {
��������if(y == 0) {
������������throw 1;
��������} else {
������������return a/b;
��������}
����} catch(int erro) {
��������if (erro == 1) {
������������cout << "Erro de divisao por zero" << endl;
��������}
����}
}*/