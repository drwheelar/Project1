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
	IMAGE *bulletpic;
	double rad;
	int x;
	int y;
	double rad;
	int speed;
	int size;
	int attack;
	int hit;
	struct bulletchain* next;
};
void putimage_a(int x, int y, IMAGE* pImg);
void RotateImageAlpha(IMAGE* after, IMAGE* before, double radian, int px, int py, bool autosize = true);
void init(item* start, int number);//初始化陨石群
void inititem(item* start);//初始化单个陨石
void updataWithoutInput(bulletchain*bullet,item*a,item*b,item*c,item*d,item*e,int*A,
	int*B,int*C,int*D,int*E,int*q,int*w,int*r,int*t,char* k);
void updataWithInput(bulletchain* bullet, item* a, item* b, item* c, item* d, item* e,double*shootrad,int*stop,
	int speed1, int size1, int attack1);
void show(IMAGE*rubbishpic,IMAGE*cover,bulletchain* bullet, item* a, item* b, item* c, item* d, item* e,IMAGE*shooter,double rad,char*k);
void solar1(IMAGE* rubbishpic, char exception[], int speed1, int size1, int attack1){
	IMAGE* cover = new IMAGE();
	loadimage(cover, _T("D:\\game\\pack\\solar1\\back\\back.png"), 1300, 700);
	putimage(0, 0, cover);
	item* oxygen = (item*)malloc(sizeof(item));
	item* carbon = (item*)malloc(sizeof(item));
	item* iron = (item*)malloc(sizeof(item));
	item* rubbish = (item*)malloc(sizeof(item));
	item* silicon = (item*)malloc(sizeof(item));
	bulletchain* bullet = NULL;
	init(oxygen, 10);
	init(carbon, 10);
	init(iron, 10);
	init(rubbish, 5);
	init(silicon, 10);
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
	ExMessage m;
	int stop = 0;
	double shootrad = 0;
	IMAGE* shooter = new IMAGE ();
	IMAGE* after = shooter;
	char key = NULL;
	loadimage(shooter, _T("D:\\game\\pack\\solar1\\shooter\\shooter.png"),260,260);
	double angle;
	while (1) {
		if (stop == 1) continue;
		show(rubbishpic,cover,bullet,oxygen,carbon,iron,silicon,rubbish,after,shootrad,exception);
		updataWithoutInput(bullet,oxygen,carbon,iron,silicon,rubbish,&oxygennumber,&carbonnumber,
			&ironnumber,&siliconnumber,&rubbishnumber,&oxygengain,&carbongain,&irongain,&silicongain,exception);
		updataWithInput(bullet, oxygen, carbon, iron, silicon, rubbish, &shootrad,& stop, speed1, size1,  attack1);

	}
}
void init(item* start,int number) {
	for (int i = 0; i < number; i++) {
		item* s = (item*)malloc(sizeof(item));
		item* last = start;
		last->next = s;
		s->next = NULL;
		srand((unsigned)time(NULL));
		last->size = rand() % 3 + 1;
		last->blood = last->size * 100;
		int a = rand() % 4;
		last->motion = 1;
		if (a == 0) {
			last->x = -50 * last->size;
			last->y = rand() % (700 + 100 * last->size) - 50 * last->size;
			last->speedx = rand() % 5+1;
			last->speedy = rand() % 7 - 3;
		}
		if (a == 2 || a == 1) {
			last->y = -50 * last->size;
			last->x = rand() % (1300 + 100 * last->size) - 50 * last->size;
			last->speedx = rand() % 11 - 5;
			last->speedy = rand() % 3+1;
		}
		if (a == 3) {
			last->x = 1300;
			last->y = rand() % (700 + 100 * last->size) - 50 * last->size;
			last->speedx = -rand() % 5+1;
			last->speedy = rand() % 7 - 3;
		}
		last = last->next;
	}
}
void inititem(item* start) {
	start = (item*)malloc(sizeof(item));
		start->next = NULL;
		srand((unsigned)time(NULL));
		start->size = rand() % 3 + 1;
		start->blood = start->size * 100;
		int a = rand() % 4;
		start->motion = 1;
		if (a == 0) {
			start->x = -50 * start->size;
			start->y = rand() % (700 + 50 * start->size) - 50 * start->size;
			start->speedx = rand() % 6;
			start->speedy = rand() % 7 - 3;
		}
		if (a == 2 || a == 1) {
			start->y = -50 * start->size;
			start->x = rand() % (1300 + 50 * start->size) - 50 * start->size;
			start->speedx = rand() % 11 - 5;
			start->speedy = rand() % 4;
		}
		if (a == 3) {
			start->x = 1300;
			start->y = rand() % (700 + 100 * start->size) - 50 * start->size;
			start->speedx = -rand() % 6;
			start->speedy = rand() % 7 - 3;
		}
}
void updataWithInput(bulletchain* bullet, item* a, item* b, item* c, item* d, item* e,double*shootrad,int*stop,
	int speed1, int size1, int attack1){
	ExMessage m;
	if (peekmessage(&m, EX_MOUSE) && m.message == WM_LBUTTONDOWN) {
		if (m.x > 1125 && m.x < 1275 && m.y>275 && m.y < 325) {
			if (*stop == 0)  *stop = 1; 
			else *stop = 0;
		}
	}
	if (_getch() == 224) {
		int key = _getch();
		if (key == 77) *shootrad += 5;
		else if (key == 75) *shootrad -= 5;
		else if (key == 72) {
			bulletchain* newbullet;
			IMAGE bulletpicture;
			loadimage(&bulletpicture, _T("D:\\game\\pack\\solar1\\shooter\\bullet.png"), 40, 40);
			newbullet->bulletpic = &bulletpicture;
			newbullet->rad = *shootrad;
			double angle = *shootrad * PI / 180;
			if (angle <= 0) {
				newbullet->x = 650 + 125 * sin(angle) - 25 * cos(angle);
				newbullet->y = 675 - 125 * cos(angle) + 25 * sin(angle);
			}
			else {
				newbullet->x = 650 + 125 * sin(angle) - 25 * cos(angle) - 25 * sin(angle);
				newbullet->y = 675 - 125 * cos(angle) + 25 * sin(angle);
			}
			newbullet->speed = speed1;
			newbullet->size = size1;
			newbullet->attack = attack1;
			newbullet->hit = 0;
			if (!bullet) bullet = newbullet;
			else {
				bulletchain* last = bullet;
				while (last->next) last = last->next;
				last->next = newbullet;
			}
		}
	}
}