#define _CRT_SECURE_NO_WARNINGS
#include <graphics.h>  
#include <stdio.h>
#include<conio.h>
#include <stdlib.h>
#include <time.h>
#include<math.h>
#pragma comment(lib, "MSIMG32.LIB")
void putimage_a(int x, int y, IMAGE* pImg);
bool login();
IMAGE* drawrubbish();
void play(IMAGE* rubbishpic, char exception[], int speed1, int size1, int attack1);
void solar1(IMAGE* rubbishpic, char exception[], double speed1, int size1, int attack1,int time1, int* a, int* b, int* c, int* d);
void premultiply(IMAGE* pImg);
void upgrade(int* speed, int* size, int* attack,int*a,int*b,int*c,int*d,int*A,int*B,int*C,int*D,int*stage);
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
		char str[] = "silion";
		IMAGE* cover = new IMAGE();
		premultiply(rubbishpic);
		//loadimage(cover, _T("D:\\game\\pack\\solar1\\background\\cover.png"), 1300, 700);
		//putimage(0, 0, cover);
		int speed = 5;
		int size = 50;
		int attack = 50;
		int oxygengain = 0;
		int carbongain = 0;
		int irongain = 0;
		int silicongain = 0;
		int oxygen = 0;
		int carbon = 0;
		int iron = 0;
		int silicon = 0;
		int stage = 0;
		solar1(rubbishpic, str, 5,50, 50,1,&oxygengain, &carbongain, &irongain, &silicongain);
		while(1){
			//upgrade(&speed, &size, &attack,&oxygengain,&carbongain,&irongain,&silicongain,
			// &oxygen,&carbon,&iron,&silicon,&stage);
		 }
	}
	return 1;
}