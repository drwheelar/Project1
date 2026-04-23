#define _CRT_SECURE_NO_WARNINGS
#include <graphics.h>  
#include <stdio.h>
#include<conio.h>
#include <stdlib.h>
#include <time.h>
#include<math.h>
//#pragma comment(lib, "MSIMG32.LIB")
void putimage_a(int x, int y, IMAGE* pImg);
bool login();
IMAGE* drawrubbish();
void play(IMAGE* rubbishpic, char exception[], int speed1, int size1, int attack1);
void solar1(IMAGE* rubbishpic, char exception[], double speed1, int size1, int attack1);
void premultiply(IMAGE* pImg);
int main() {
	initgraph(1300, 700);
	setbkmode(TRANSPARENT);
	settextstyle(25, 0, _T("Consolas"));
	IMAGE cover, Login;
	loadimage(&cover, _T("D:\\game\\pack\\login\\cover.png"), 1300, 700);
	loadimage(&Login, _T("D:\\game\\pack\\login\\start.png"), 400, 160);
	putimage(0, 0, &cover);
	putimage_a(450, 500, &Login);
	IMAGE* rubbishpic;
	if (login()) {
		rubbishpic = drawrubbish();
		setbkcolor(BLUE);
		char str[] = "silicon";
		IMAGE* cover = new IMAGE();
		premultiply(rubbishpic);
		//loadimage(cover, _T("D:\\game\\pack\\solar1\\background\\cover.png"), 1300, 700);
		//putimage(0, 0, cover);
		 play(rubbishpic,str,5,50,50);
		 while(1){}
	}
	return 1;
}
void play(IMAGE* rubbishpic, char exception[], int speed1, int size1, int attack1) {
	solar1(rubbishpic,  exception,  speed1, size1,  attack1);
}