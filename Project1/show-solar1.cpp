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
void RotateImageAlpha(IMAGE* after, IMAGE* before, double radian, int px, int py, bool autosize = true);
void show(IMAGE* rubbishpic, IMAGE* cover, bulletchain* bullet, item* oxygen, item* carbon, item* iron,
	item* silicon, item* rubbish, IMAGE* after,double shootrad, char exception[]) {
	BeginBatchDraw();
	putimage(0, 0, cover);
	bulletchain* thisbullet = bullet;

	while (thisbullet) {
		if (thisbullet->bulletpic != NULL) putimage_a(thisbullet->x, thisbullet->y, thisbullet->bulletpic);
		thisbullet = thisbullet->next;
	}
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
	IMAGE k;
	if (strcmp(exception, "oxygen") != 0) {
		loadimage(&k, _T("D:\\game\\pack\\solar1\\oxygen\\1.png"), 150, 150);
		item*last = oxygen;
		while (last) {
			Resize(&k, (last->size)*50,( last->size) * 50);
			putimage_a(last->x, last->y,&k);
			last = last->next;
		}
	}
	if(strcmp(exception, "carbon") != 0){
		item* last = carbon;
		loadimage(&k, _T("D:\\game\\pack\\solar1\\carbon\\1.png"), 150, 150);
		while (last) {
			Resize(&k, (last->size) * 50,( last->size )* 50);
			putimage_a(last->x, last->y, &k);
			last = last->next;
		}
	}
	if (strcmp(exception, "silicon") != 0) {
		item* last = silicon;
		loadimage(&k, _T("D:\\game\\pack\\solar1\\silicon\\1.png"), 150, 150);
		while (last) {
			Resize(&k, (last->size )* 50,( last->size) * 50);
			putimage_a(last->x, last->y,& k);
			last = last->next;
		}
	}
	if (strcmp(exception, "iron") != 0) {
		item* last = iron;
		loadimage(&k, _T("D:\\game\\pack\\solar1\\iron\\1.png"), 150, 150);
		while (last) {
			Resize(&k,( last->size) * 50,( last->size) * 50);
			putimage_a(last->x, last->y, &k);
			last = last->next;
		}
	}
	item* last = rubbish;
	while (last) {
		Resize(rubbishpic, last->size * 50, last->size * 50);
		putimage_a(last->x, last->y, rubbishpic);
		last = last->next;
	}
	IMAGE* before = new IMAGE();
	IMAGE* d = new IMAGE();
	loadimage(before, _T("D:\\game\\pack\\solar1\\shooter\\shooter.png"), 250, 250);
	double angle = shootrad * PI / 180;
	RotateImageAlpha(d, before, angle, 125, 125, false);
	putimage_a(525, 550, d);
	delete(before);
	delete(d);
	FlushBatchDraw();
	EndBatchDraw();
}