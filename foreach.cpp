#include <iostream>
#include <cstring>
using namespace std;

int main() {
	char ola[] = "Hello Anatoli!";
	cout << "Tamanho: " << strlen(ola) << endl;
	// auto: detects type
	for (auto x : ola) {
		cout << "Character: " << x << endl;
	}
}