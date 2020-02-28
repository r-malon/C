#include <iostream>
using namespace std;

int main() {
	int size;
	cout << "Enter the diamond's size: ";
	cin >> size;

	for (int i = 1; i < size; i++) {
		cout << string((size / 2) - (size % i), '*') << i << endl;
	}
	return 0;
}