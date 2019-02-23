#include <iostream>
using namespace std;
void proc(int a, int b){
	//procedimento: NÃO retorna valor
	cout << "procedimento: " << a+b;
}
int func(int a, int b){
	//função: retorna valor
	return a*b;
}
int main(void){
	proc(7, 8);
	func(5, 6);
	return 0;
}
