#define _CRT_SECURE_NO_WARNINGS
#include <graphics.h>  
#include <stdio.h>
#include<conio.h>
#include <stdlib.h>
#include <time.h>
#pragma comment(lib, "MSIMG32.LIB")
void putimage_a(int x, int y, IMAGE* pImg);
void login();
IMAGE* drawrubbish();
void solar1(IMAGE* rubbish);
int main() {
	initgraph(1300, 700);
	setbkmode(TRANSPARENT);
	settextstyle(25, 0, _T("Consolas"));
	IMAGE cover, Login;
	loadimage(&cover, _T("D:\\game\\pack\\login\\cover.png"), 1300, 700);
	loadimage(&Login, _T("D:\\game\\pack\\login\\start.png"), 400, 160);
	putimage(0, 0, &cover);
	putimage_a(450, 500, &Login);
	IMAGE* rubbish;
		login();
		rubbish=drawrubbish();
		setbkcolor(BLUE);
		BeginBatchDraw();
		cleardevice();
		putimage_a(0, 0,rubbish);
		FlushBatchDraw();
		EndBatchDraw();
		while(1){}

	
	return 1;
}