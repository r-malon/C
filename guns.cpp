#include <iostream>
#include <windows.h>
#include <clocale>
using namespace std;
class guns{
	//private por padrão
	public:
		guns(string _name,string _mode,int _ammo, int _rpm): //construtor
			name(_name),mode(_mode),rpm(_rpm),ammo(_ammo),pente(_ammo){};
		string name;
		string mode;
		int ammo;
		int rpm;
		int changemode(){
			cout << "Diga um modo: ";
			cin >> mode;
		}
		int reload(){
			ammo = pente;
		}
		void shoot(){
			if(mode=="semi-auto"){
				ammo -= 1;
				Sleep(60000/rpm); //milisegundos
			}
			if(mode=="burst"){
				for(int i=0;i<3;i++){
					ammo -= 1;
					Sleep(60000/rpm);
				}
				//ammo -= 3;
			}
			else{
				changemode();
			}
		}
	private:
		int pente = ammo;
	//protected:
};
int main(){
	setlocale(LC_ALL, "");
	guns fuzil("m16", "burst", 30, 120);
	/*fuzil.name = "M-16";
	fuzil.ammo = 50;*/
	cout << "O fuzil " << fuzil.name << " atira em modo " << fuzil.mode << " tem " << fuzil.ammo << " projéteis\n";
	fuzil.shoot();
	//fuzil.changemode();
	//fuzil.shoot();
	cout << "ammo: " << fuzil.ammo << endl;
	fuzil.reload();
	cout << "carregado: " << fuzil.ammo;
}
