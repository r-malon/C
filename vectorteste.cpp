#include <vector>
#include <iostream>
using namespace std;

int main(){
	int size=5;
	vector<int> arr(size);//abre espaço para 5 int definidos como 0
	for(int i=0;i<size;i++){
		arr[i]=i+1;
	}
	for(int i=0;i<size;i++){
		cout << arr[i];
	}
}
