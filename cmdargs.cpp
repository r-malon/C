#include <iostream>
using namespace std;
int main(int argc, char *argv[]/*, char *envp[] hack?*/){//needed to execute command line args
	//argc: nº of strings pointed to argv
	//argv: array of arguments
	for(int i = 0; i < argc; i++){
		cout << "Os Argv são: " << argv[i] << endl;//argv[0] é o nome do programa
	}
}