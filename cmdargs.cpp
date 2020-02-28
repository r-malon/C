#include <iostream>
using namespace std;

int main(int argc, char *argv[]/*, char *envp[] hack?*/) {
	// needed to receive command line args
	// argc: # of strings pointed to argv
	// argv: array of arguments
	for (int i = 0; i < argc; i++) {
		cout << "The args are: " << argv[i] << endl; // argv[0] is program name
	}
}