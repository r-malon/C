#include <iostream>
using namespace std;

int main(int argc, char const *argv[]) {
	int a, b;
	scanf("%d %d", &a, &b);
	b = (a + b) - (a = b);
	printf("%d %d", a, b);
	return 0;
}