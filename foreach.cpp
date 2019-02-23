#include <iostream>
#include <cstring>
using namespace std;
int main(){
	char ola[] = "ola pessoas!";
	cout << "Tamanho: " << strlen(ola) << endl;
	for(auto x : ola){ //auto: detecta o tipo
		cout << "Letra: " << x << endl;
	}
}