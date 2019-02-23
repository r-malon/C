#include <iostream>
#include <windows.h>
using namespace std;
int main(){
	for(int i=0;i<80;i+=10){
		SetCursorPos(70*i, 10*i);
		mouse_event(MOUSEEVENTF_LEFTDOWN, 50*i,20*i,0,0);
		mouse_event(MOUSEEVENTF_LEFTUP, 50*i,20*i,0,0);
		Sleep(300);
	}
	system("start C:/Users/RAFAEL/Videos/mini-virus.exe"); //call executa na mesma janela
}