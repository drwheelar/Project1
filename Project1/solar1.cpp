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
void init(item** head, int num);//初始化陨石群
void inititem(item* start);//初始化单个陨石
void updataWithoutInput(bulletchain** bullet, item** oxygen, item** carbon, item** iron, item** silicon, item** rubbish,
	int* oxygennumber, int* carbonnumber, int* ironnumber, int* siliconnumber, int* rubbishnumber, int* oxygengain,
	int* carbongain, int* irongain, int* silicongain, char exception[]);
void updataWithInput(bulletchain** bullet, item* a, item* b, item* c, item* d, item* e,double*shootrad,int*stop,
	double speed1, int size1, int attack1,IMAGE *bulletimg);
void show(IMAGE* rubbishpic, IMAGE* cover, bulletchain* bullet, item* oxygen, item* carbon, item* iron,
	item* silicon, item* rubbish, IMAGE* after, double shootrad, char exception[]);
void solar1(IMAGE* rubbishpic, char exception[], double speed1, int size1, int attack1){
	static IMAGE* bulletimg=new IMAGE();
	loadimage(bulletimg, _T("D:\\game\\pack\\solar1\\shooter\\bullet.png"), 40, 40);
	premultiply(bulletimg);
	IMAGE* cover = new IMAGE();
	loadimage(cover, _T("D:\\game\\pack\\solar1\\background\\cover.png"), 1300, 700);
	//putimage(0, 0, cover);
	IMAGE* shooter = new IMAGE ();
	IMAGE* after = shooter;
	loadimage(shooter, _T("D:\\game\\pack\\solar1\\shooter\\shooter.png"),260,260);
	premultiply(shooter);
	//putimage(0, 0, shooter);
	/*IMAGE* l = new IMAGE();
	IMAGE oxygenpic[3];
	loadimage(l, _T("D:\\game\\pack\\solar1\\oxygen\\1.png"), 150, 150);
	for (int i = 0; i < 3; i++) {
		Resize(l, (i + 1) * 50, (i + 1) * 50);
		oxygenpic[i] = *l;
	}
	IMAGE ironpic[3];
	loadimage(l, _T("D:\\game\\pack\\solar1\\iron\\1.png"), 150, 150);
	for (int i = 0; i < 3; i++) {
		Resize(l, (i + 1) * 50, (i + 1) * 50);
		ironpic[i] = *l;
	}
	IMAGE silliconpic[3];
	loadimage(l, _T("D:\\game\\pack\\solar1\\sillocon\\1.png"), 150, 150);
	for (int i = 0; i < 3; i++) {
		Resize(l, (i + 1) * 50, (i + 1) * 50);
		silliconpic[i] = *l;
	}
	IMAGE carbonpic[3];
	loadimage(l, _T("D:\\game\\pack\\solar1\\carbon\\1.png"), 150, 150);
	for (int i = 0; i < 3; i++) {
		Resize(l, (i + 1) * 50, (i + 1) * 50);
		carbonpic[i] = *l;
	}
	IMAGE rubbishpicchain[3];
	l = rubbishpic;
	for (int i = 0; i < 3; i++) {
		Resize(l, (i + 1) * 50, (i + 1) * 50);
		rubbishpicchain[i] = *l;
	}
	delete(l);*/
	srand((unsigned)time(NULL));
	item* oxygen = NULL; init(&oxygen, 5);
	item* carbon = NULL; init(&carbon, 5);
	item* iron = NULL; init(&iron, 5);
	item* rubbish = NULL; init(&rubbish, 5);
	item* silicon = NULL; init(&silicon, 5);
	bulletchain* bullet = NULL;
	//while (1);
	int gamestop = 1;
	int oxygennumber = 10;
	int ironnumber = 10;
	int carbonnumber = 10;
	int rubbishnumber = 5;
	int siliconnumber = 10;
	int oxygengain = 0;
	int carbongain = 0;
	int irongain = 0;
	int silicongain = 0;
	int stop = 0;
	double shootrad = 0;
	while (1) {
		if (stop == 1) continue;
		srand((unsigned)time(NULL));
		updataWithoutInput(&bullet,&oxygen,&carbon,&iron,&silicon,&rubbish,&oxygennumber,&carbonnumber,
			&ironnumber,&siliconnumber,&rubbishnumber,&oxygengain,&carbongain,&irongain,&silicongain,exception);
		updataWithInput(&bullet, oxygen, carbon, iron, silicon, rubbish, &shootrad,& stop, speed1, size1,  attack1,bulletimg);
		show(rubbishpic, cover, bullet, oxygen, carbon, iron, silicon, rubbish, after, shootrad, exception);

	}
}
void init(item** head, int num) {
	*head = NULL;
	item* last = NULL;
	for (int i = 0; i < num; i++) {
		item* node = new item();
		inititem(node);
		if (*head == NULL) {
			*head = node;
			last = node;
		}
		else {
			last->next = node;
			last = node;
		}
	}
}
void inititem(item* start) {
	start->next = NULL;
	start->size = rand() % 3 + 1;
	printf("%d\n", start->size);
	start->blood = start->size * 100;
	printf("%d\n", start->blood);
	int a = rand() % 4;
	start->motion = 1;
	if (a == 0) {
		start->x = -50 * start->size;
		start->y = rand() % (700 + 50 * start->size) - 50 * start->size;
		start->speedx = rand() % 6+1;
		start->speedy = rand() % 7 - 3;
	}
	if (a == 2 || a == 1) {
		start->y = -50 * start->size;
		start->x = rand() % (1300 + 50 * start->size) - 50 * start->size;
		start->speedx = rand() % 11 - 5;
		start->speedy = rand() % 4+1;
	}
	if (a == 3) {
		start->x = 1300;
		start->y = rand() % (700 + 100 * start->size) - 50 * start->size;
		start->speedx = -rand() % 6+1;
		start->speedy = rand() % 7 - 3;
	}
	printf("%d\n", start->y);
}

void updataWithInput(bulletchain** bullet, item* a, item* b, item* c, item* d, item* e,double*shootrad,int*stop,
	double speed1, int size1, int attack1,IMAGE *bulletimg){
	ExMessage m;
	if (peekmessage(&m, EX_MOUSE) && m.message == WM_LBUTTONDOWN) {
		if (m.x > 1125 && m.x < 1275 && m.y>275 && m.y < 325) {
			if (*stop == 0)  *stop = 1; 
			else *stop = 0;
		}
	}
	if (_kbhit()) {
		if (_getch() == 224) {
			int key = _getch();
			if (key == 77) *shootrad += 5;
			else if (key == 75) *shootrad -= 5;
			else if (key == 72) {
				bulletchain* newbullet = new bulletchain();
				newbullet->bulletpic = new IMAGE(40, 40);
				double angle = *shootrad * PI / 180;
				newbullet->rad = angle;
				newbullet->next = NULL;
				RotateImageAlpha(newbullet->bulletpic, bulletimg, newbullet->rad, 20, 20, false);
				if (angle <= 0) {
					newbullet->x = 650 + 125 * sin(angle) - 20 * cos(angle);
					newbullet->y = 675 - 125 * cos(angle) + 20 * sin(angle);
				}
				else {
					newbullet->x = 650 + 125 * sin(angle)   - 20 * cos(angle) - 40 * sin(angle);
					newbullet->y = 675 - 105 * cos(angle) - 20 * sin(angle);
				}
				newbullet->speed = 5;
				newbullet->size = 50;
				newbullet->attack = 50;
				newbullet->hit = 0;
				if (!*bullet) {
					*bullet = newbullet;
					IMAGE* a = NULL;
				}
				else {
					bulletchain* last = *bullet;
					while (last->next) last = last->next;
					last->next = newbullet;
				}
			}
		}
	}
}