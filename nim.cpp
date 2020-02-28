#include <iostream>
#include <clocale>
#include <ctime>
using namespace std;

int main(void) {
	int pile_number;
	cout << "Type the piles number: ";
	cin >> pile_number;
	int piles[pile_number];
	srand(time(0));

	for (int i = 0; i < pile_number; ++i) {
		piles[i] = rand() % 10 + 1;
		cout << piles[i] << endl;
	}
}