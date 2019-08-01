#include <iostream>
#include <algorithm>
using namespace std;

int main(){
	int x[15];
	for(int i=0;i<15;i++){
		x[i] = rand()%9;
	}

	for(int i=0;i<10;i++){
		cout << "Numero " << i << " aparece " << count(x,x+15,i) << endl;
	}
}
