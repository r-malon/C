#include <iostream>
using namespace std;
class forma{
	public:
		int alt, larg;
		//void fazer(int, int);
		int area(void){
			return(alt*larg);
		}
};
/*forma::forma(int x, int y){
	h = x;
	l = y;
}*/
int main(){
	forma bla;
	forma ble;		//tudoerradoaki!
	cout << "diga: ";
	cin >> bla.alt;
	cout << "dnovo: ";
	cin >> bla.larg;
	/*bla.h = 10;
	bla.l = 15;*/
	cout << "area1: " << bla.area() << " area2: " << ble.area();
}
