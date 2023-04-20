#include <iostream>
using namespace std;

template <class T>
bool ansisupported (T x) { return true; }

int main() {
	if (ansisupported(0)) cout << "ANSI OK";
	return 0;
}
