#include <iostream>
#include <fstream>
using namespace std;
int main(){
	char *x = new char;
	fstream bla;
	fstream yep;
	yep.open("C:/Users/RAFAEL/Music/cadastro.txt",ios::in | ios::out);
	bla << "jailson sauda cpp dinamico!\n";
	yep >> x;
	cout << x;
	void close();
}
