#include <iostream>
using namespace std;
int main(int argc, char *argv[]/*, char *envp[] hack?*/){//needed to execute command line args
	//argc: n� of strings pointed to argv
	//argv: array of arguments
	for(int i = 0; i < argc; i++){
		cout << "Os Argv s�o: " << argv[i] << endl;//argv[0] � o nome do programa
	}
}