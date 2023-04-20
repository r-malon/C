#include <iostream>
#include <algorithm>
#include <windows.h>
using namespace std;

int main() {
	int x;
	int y[20];
	for (int i = 0; i < 10; i++) {
		cout << "\nEnter your number: ";
		cin >> x;
		y[i] = x;
		int cont = count(y, y+20,x);
		if (cont > 1) {
			cout << "Automatic message";
		}
		else {
			cout << "Hello, I will answer you!";
		}
		Sleep(500); //miliseconds!
	}
	return 0;
}