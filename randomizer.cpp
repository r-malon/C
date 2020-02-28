#include <iostream>
#include <cstring>
#include <clocale>
#include <ctime>
using namespace std;

int main() {
	setlocale(LC_ALL, "");
	char word[20];
	cout << "Digite: ";
	cin >> word;
	int c = strlen(word);
	int list[c];

	for(int i = 0; i < c; i++) {
		int y = srand(time(NULL)) % c;
		list[i] = y;
	}

	for(int i = 0; i < c; i++) {
		cout << word[list[i]];
	}
}