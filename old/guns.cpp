#include <iostream>
#include <windows.h>
#include <clocale>
using namespace std;

class Gun {
	//private by default
	public:
		Gun(string _name, string _mode, int _ammo, int _fire_rate): //constructor
			name(_name), mode(_mode), fire_rate(_fire_rate), ammo(_ammo), pente(_ammo){};
		string name;
		string mode;
		int ammo;
		int fire_rate;

		int changemode() {
			cout << "Diga um modo: ";
			cin >> mode;
		}

		int reload() {
			ammo = pente;
		}

		void shoot() {
			if (mode == "semi-auto") {
				ammo -= 1;
				Sleep(60000/fire_rate); //miliseconds
			}
			if (mode == "burst") {
				for(int i = 0; i < 3; i++) {
					ammo -= 1;
					Sleep(60000/fire_rate);
				}
				//ammo -= 3;
			}
			else {
				changemode();
			}
		}
	private:
		int pente = ammo;
	//protected:
};

int main() {
	setlocale(LC_ALL, "");
	Gun rifle("M16", "burst", 30, 120);
	/*rifle.name = "M-16";
	rifle.ammo = 50;*/
	cout << "O fuzil " << rifle.name << " atira em modo " << rifle.mode << " e tem " << rifle.ammo << " projéteis\n";
	rifle.shoot();
	//rifle.changemode();
	//rifle.shoot();
	cout << "Ammo: " << rifle.ammo << endl;
	rifle.reload();
	cout << "Loaded: " << rifle.ammo;
}