#include <iostream>
using namespace std;

class Rectangle {
	public:
		int width, height;
		//void fazer(int, int);
		int area(void) {
			return (width * height);
		}
};

/*Rectangle::Rectangle(int x, int y) {
	h = x;
	l = y;
}*/

int main() {
	Rectangle bla;
	Rectangle ble;
	cout << "Enter width: ";
	cin >> bla.width;
	cout << "Enter height: ";
	cin >> bla.height;
	/*bla.h = 10;
	bla.l = 15;*/
	cout << "area1: " << bla.area() << "\narea2: " << ble.area();
}