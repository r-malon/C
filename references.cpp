#include <iostream>
using namespace std;

int main(){
	int x;
	char y[30];
	int& ref = x;
	char& ref2[] = y;
	x = 35;
	y = "olajailson";
	cout << "referencia: " << ref << " e " << ref2;
}
