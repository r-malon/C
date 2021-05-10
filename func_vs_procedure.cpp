#include <iostream>
using namespace std;

void proc(int a, int b) {
	// procedure: doesn't return
	cout << "A + B: " << a + b;
}

int func(int a, int b) {
	// function: needs to return value
	return a * b;
}

int main() {
	proc(7, 8);
	func(5, 6);
	return 0;
}