#include <iostream>
using namespace std;
extern int i;
int main(){
	cout << "main do arquvi externo" << endl;
}
void arq_externo(){
	cout << "ARQUIVO EXTERNO -> " << i << "!!!";
}
