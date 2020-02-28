#include <iostream>
using namespace std;

int main() {
	char pl[20];
	char *pt;
	pt = &pl;
	int list[];

	for (int i = 0; i < 5; i++) {
		cout << "Enter a word: ";
		cin >> pl;
		list[i] = pt;
	}
}