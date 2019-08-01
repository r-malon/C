#include <iostream>
#include <algorithm>
#include <string>
using namespace std;

int main(){
	char ola[30];
	int a=89;
	int b=27;
	int *pt=&a;
	int *pj=&b;
	//cout<<"bla: ";
	//std::getline(cin,ola);
	//cout << "isso " << ola << endl;
	cout << "endereco: " << pt << endl;
	cout << "valor do endereco: " << *pt << endl;
	cout << "soma de a+b: " << *pt+*pj;
}
