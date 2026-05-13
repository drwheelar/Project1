#define _CRT_SECURE_NO_WARNINGS
#include <graphics.h>  
#include <stdio.h>
#include <stdlib.h>
#include<conio.h>
#include <time.h>
#include<math.h>
#include<string.h>
#define PI 3.14159265358979323846
#pragma comment(lib, "MSIMG32.LIB")
typedef struct item {
	int speedx;
	int speedy;
	int x;
	int y;
	int blood;
	int motion;
	int size;
	struct item* next;
};
typedef struct bulletchain {
	IMAGE* bulletpic;
	int x;
	int y;
	double rad;
	int speed;
	int size;
	int attack;
	int hit;
	struct bulletchain* next;
};
void premultiply(IMAGE* pImg);
void putimage_a(int x, int y, IMAGE* pImg);
void Resize_a(IMAGE* pDestImg, IMAGE* pSrcImg, int destWidth, int destHeight);
void RotateImageAlpha(IMAGE* after, IMAGE* before, double radian, int px, int py, bool autosize = true);
int show(IMAGE* rubbishpic, IMAGE* cover, bulletchain* bullet, item* oxygen, item* carbon, item* iron,
	item* silicon, item* rubbish, IMAGE* after,double shootrad, int* oxygengain,int* carbongain, int* irongain, 
	int* silicongain, char exception[],int time1) {
	BeginBatchDraw();
	settextstyle(25, 0, _T("微软雅黑"));
	putimage(0, 0, cover);
	bulletchain* thisbullet = bullet;

	/*int a = 0;
	while (a<50) {
		if (a == 40) {
			last = rubbish;
			a = 50;
			after = rubbishpic;
		}
		if (a == 30 && exception == "silicon") {
			last = rubbish;
			a = 50;
			after = rubbishpic;
		}
		if (a == 30 && exception != "silicon") {
			last = silicon;
			a = 40;
			loadimage(after, _T("D:\\game\\pack\\solar1\\sillicon\\1.png"), 150, 150);
		}
		if (a == 20 && exception == "iron") {
			last = silicon;
			a = 40;
			loadimage(after, _T("D:\\game\\pack\\solar1\\sillicon\\1.png"), 150, 150);
		}
		if (a == 20 && exception != "iron") {
			last = iron;
			a = 30;
			loadimage(after, _T("D:\\game\\pack\\solar1\\iron\\1.png"), 150, 150);
		}
		if (a == 10 && exception == "carbon") {
			last = iron;
			a = 30;
			loadimage(after, _T("D:\\game\\pack\\solar1\\iron\\1.png"), 150, 150);
		}
		if (a == 10 && exception != "carbon") {
			last = carbon;
			a = 20;
			loadimage(after, _T("D:\\game\\pack\\solar1\\carbon\\1.png"), 150, 150);
		}
		if (a == 0 && exception == "oxygen") {
			last = carbon;
			a = 20;
			loadimage(after, _T("D:\\game\\pack\\solar1\\carbon\\1.png"), 150, 150);
		}
		if (a == 0 && exception != "oxygen") {
			last = oxygen;
			a = 10;
			loadimage(after, _T("D:\\game\\pack\\solar1\\oxygen\\1.png"), 150, 150);
		}*/
	IMAGE l;
	IMAGE k;
	IMAGE m;
	IMAGE* before = new IMAGE();
	IMAGE* d = new IMAGE();
	loadimage(before, _T("D:\\game\\pack\\solar1\\shooter\\shooter.png"), 250, 250);
	double angle = shootrad * PI / 180;
	RotateImageAlpha(d, before, angle, 125, 125, false);
	while (thisbullet) {
		if (thisbullet->bulletpic != NULL) putimage_a(thisbullet->x, thisbullet->y, thisbullet->bulletpic);
		thisbullet = thisbullet->next;
	}
	putimage_a(525, 550, d);
	loadimage(&m, _T("D:\\game\\pack\\solar1\\background\\table.png"), 200, 40);
	if (strcmp(exception, "oxygen") != 0) {
		loadimage(&l, _T("D:\\game\\pack\\solar1\\oxygen\\1.png"), 150, 150);
		item*last = oxygen;
		while (last) {
			Resize_a(&k,&l, (last->size)*50,( last->size) * 50);
			putimage_a(last->x, last->y,&k);
			last = last->next;
		}
	}
	if(strcmp(exception, "carbon") != 0){
		item* last = carbon;
		loadimage(&l, _T("D:\\game\\pack\\solar1\\carbon\\1.png"), 150, 150);
		while (last) {
			Resize_a(&k, &l, (last->size) * 50,( last->size )* 50);
			putimage_a(last->x, last->y, &k);
			last = last->next;
		}
	}
	if (strcmp(exception, "iron") != 0) {
		item* last = iron;
		loadimage(&l, _T("D:\\game\\pack\\solar1\\iron\\1.png"), 150, 150);
		while (last) {
			Resize_a(&k, &l, (last->size) * 50, (last->size) * 50);
			putimage_a(last->x, last->y,&k);
			last = last->next;
		}
	}
	item* last = rubbish;
	while (last) {
		Resize_a(&k, rubbishpic, last->size * 50, last->size * 50);
		putimage_a(last->x, last->y, &k);
		last = last->next;
	}
	if (strcmp(exception, "silicon") != 0) {
		item* last = silicon;
		loadimage(&l, _T("D:\\game\\pack\\solar1\\sillicon\\1.png"), 150, 150);
		while (last) {
			Resize_a(&k, &l, (last->size) * 50, (last->size) * 50);
			putimage_a(last->x, last->y, &k);
			last = last->next;
		}
		putimage_a(0, 205, &m);
		wchar_t oxygenshow[15] = _T("硅收获：");
		wchar_t oxygentext[15];
		swprintf(oxygentext, sizeof(oxygentext), L"%d", *silicongain);
		wcscat(oxygenshow, oxygentext);
		outtextxy(10, 212, oxygenshow);
	}
	putimage_a(0, 155, &m);
	wchar_t oxygenshow[15] = _T("铁收获：");
	wchar_t oxygentext[15];
	swprintf(oxygentext, sizeof(oxygentext), L"%d", *irongain);
	wcscat(oxygenshow, oxygentext);
	outtextxy(10, 162, oxygenshow);
	putimage_a(0, 55, &m);
	wchar_t oxygenshow1[15] = _T("氧收获：");
	swprintf(oxygentext, sizeof(oxygentext), L"%d", *oxygengain);
	wcscat(oxygenshow1, oxygentext);
	outtextxy(10, 62, oxygenshow1);
	putimage_a(0, 105, &m);
	wchar_t oxygenshow2[15] = _T("碳收获：");
	swprintf(oxygentext, sizeof(oxygentext), L"%d", *carbongain);
	wcscat(oxygenshow2, oxygentext);
	outtextxy(10, 112, oxygenshow2);
	loadimage(&l, _T("D:\\game\\pack\\solar1\\background\\clock.png"), 40, 40);
	putimage_a(0, 5, &l);
	time_t timestart = time(NULL);
	int timepass =  timestart-time1;
	int resttime = 300-timepass;
	wchar_t timetext[15];
	swprintf(timetext, sizeof(timetext), L"%d", resttime);
	outtextxy(50, 12, timetext);
	delete(before);
	delete(d);
	FlushBatchDraw();
	EndBatchDraw();
	return resttime;
}