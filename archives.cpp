#include <iostream>
#include <fstream>
using namespace std;

int main() {
	char *x = new char;
	fstream bla;
	fstream yep;
	yep.open("C:/test.txt", ios::in | ios::out);
	bla << "Hello World!\n";
	yep >> x;
	cout << x;
	void close();
}