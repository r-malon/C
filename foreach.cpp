#include <iostream>
#include <cstring>
using namespace std;

int main() {
	char ola[] = "Hello Anatoli!";
	cout << "Tamanho: " << strlen(ola) << endl;
	for (auto x : ola) { //auto: detects type
		cout << "Character: " << x << endl;
	}
}