#include <iostream>
#include <cstring>
#include <clocale>
#include <ctime>
using namespace std;

int main(){
	setlocale(LC_ALL, "");
	char word[20];
	cout << "Digite:";
	cin >> word;
	int c = strlen(word);
	int lst[c];

	for(int i=0;i++;i<c){
		int y=srand(time(NULL))%c;
		lst[i] = y;
	}

	for(int i=0;i<c;i++){
		cout << word[lst[i]];
	}
}