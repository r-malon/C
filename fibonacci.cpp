#include <iostream>
using namespace std;
int main(void){
	unsigned int prev1 = 1;
	unsigned int prev2 = 1;
	for(int i=1; i<50; i++){
		//cout << "Fibonacci!" << endl;
		cout << i << " - " << prev1 << endl;
		cout << i + 1 << " - " << prev2 << endl;
		prev1 = prev1 + prev2;
		prev2 = prev1 + prev2;
	}
}
