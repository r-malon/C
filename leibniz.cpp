#include <iostream>
using namespace std;

int main() {
	bool neg = true;
	double result = 1;

	for (int i = 3; i < 999999; i = i + 2) {
		if (neg) {
			result -= 1.0/i;
		}
		else {
			result += 1.0/i;
		}
		neg = not neg;
	}

	cout << result * 4.0;
	return 0;
}