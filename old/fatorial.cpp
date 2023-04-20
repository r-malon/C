#include <iostream>
using namespace std;

int factorial(int n) {
	int x = 1;
	for (int i=1; i<=n; i++) {
		x *= i;
	}
	return x;
}

int main() {
	int n;
	cout << "Enter: ";
	cin >> n;
	int result = factorial(n);
	cout << result << endl;
	return 0;
}