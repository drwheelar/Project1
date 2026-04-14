#define _CRT_SECURE_NO_WARNINGS
#include <graphics.h>  
#include <stdio.h>
#include <stdlib.h>
#include<conio.h>
#include <time.h>
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
	int x;
	int y;
	int speed;
	int size;
	int attack;
	int hit;
	struct bulletchain* next;
};
void putimage_a(int x, int y, IMAGE* pImg);
void init(item* start, int number);//初始化陨石群
void inititem(item* start);//初始化单个陨石
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
	while (1) {
		if (peekmessage(&m, EX_MOUSE)&&m.message == WM_LBUTTONDOWN) {
			if (m.x > 1125 && m.x < 1275 && m.y>275 && m.y < 325) {
				if (stop == 0) { stop = 1; continue; }
				else stop = 0;
			}
		}
		if (stop ==1) continue;
		int a = 0;
		while (a < 50) {
			item* last=NULL;
			if (a == 40) {
				last = rubbish;
				a = 50;
			}
			if (a == 30 && exception == "silicon") {
				last = rubbish;
				a = 50;
			}
			if (a == 30 && exception != "silicon") {
				last = silicon;
				a = 40;
			}
			if (a == 20 && exception == "iron") {
				last = silicon;
				a = 40;
			}
			if (a == 20 && exception != "iron") {
				last = iron;
				a = 30;
			}
			if (a == 10 && exception == "carbon") {
				a = 30;
			}
			if (a == 10 && exception != "carbon") {
				last = carbon;
				a = 20;
			}
			if (a == 0 && exception == "oxygen") {
				last = carbon;
				a = 20;
			}
			if (a == 0 && exception != "oxygen") {
				last = oxygen;
				a = 10;
			}
			bulletchain* thisbullet = bullet;
			while (thisbullet) {
				item* head = last;
				item* rlast = last;
				while (rlast) {
					if (((thisbullet->x + thisbullet->size) > rlast->x || (thisbullet->x - thisbullet->size) < (rlast->x + 100 * rlast->size)) &&
						((thisbullet->y + thisbullet->size) > rlast->y || (thisbullet->y - thisbullet->size) < (rlast->y + 100 * rlast->size))) {
						rlast->blood -= thisbullet->attack;//陨石扣血
						thisbullet->hit++;
						if (rlast->blood <= 0) {
							switch (a) {
							case 10:
								oxygengain += (rlast->size)*10;
								oxygennumber--;
								break;
							case 20:
								carbongain += (rlast->size) * 10;
								carbonnumber--;
								break;
							case 30:
								irongain += (rlast->size) * 10; 
								ironnumber--;
								break;
							case 40:
								silicongain += (rlast->size) * 10; 
								siliconnumber--;
								break;
							case 50:rubbishnumber--; break;
							}//计算材料捕获数，减少陨石总量
							if (rlast == last) {
								last = last->next;
								free(rlast);
								rlast = last;
								head = last;
							}
							else {
								rlast = rlast->next;
								free(head->next);
								head->next = rlast;
							}//删除空血量陨石
						}
						else {
							if (last != rlast) {
								head = head->next;
							}
							rlast = rlast->next;
						}
					}//判定受击陨石
				}
				thisbullet = thisbullet->next;
			}
		}//判定受击陨石，陨石扣血，删除空血量陨石，计算材料捕获数，减少陨石总量
		bulletchain* thisbullet = bullet;
		bulletchain* headbullet = thisbullet;
		while (thisbullet) {
			if (thisbullet->hit > 0){
				if (thisbullet == bullet) {
					bullet = bullet->next;
					thisbullet = bullet;
					headbullet = bullet;
				}
				else {
					thisbullet = thisbullet->next;
					free(headbullet->next);
					headbullet->next = thisbullet;
				}
			}
			else {
				headbullet = thisbullet;
				thisbullet = thisbullet->next;
			}
		}//删除受击子弹
		if (ironnumber < 10&&exception!="iron") {
			srand((unsigned)time(NULL));
			int num= rand() %  50+ 1;
			if (num == 1) {
				item* last = iron;
				while (last->next) last = last->next;
				inititem(last->next);
			}
		}
		if (oxygennumber < 10&&exception!="oxygen") {
			srand((unsigned)time(NULL));
			int num = rand() % 50 + 1;
			if (num == 1) {
				item* last = oxygen;
				while (last->next) last = last->next;
				inititem(last->next);
			}
		}
		if (siliconnumber < 10&&exception!="silicon") {
			srand((unsigned)time(NULL));
			int num = rand() % 50 + 1;
			if (num == 1) {
				item* last = silicon;
				while (last->next) last = last->next;
				inititem(last->next);
			}
		}
		if (carbonnumber < 10&&exception!="carbon") {
			srand((unsigned)time(NULL));
			int num = rand() % 50 + 1;
			if (num == 1) {
				item* last = carbon;
				while (last->next) last = last->next;
				inititem(last->next);
			}
		}//判定是否增加陨石
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
			start->y = rand() % (700 + 100 * start->size) - 50 * start->size;
			start->speedx = rand() % 6;
			start->speedy = rand() % 7 - 3;
		}
		if (a == 2 || a == 1) {
			start->y = -50 * start->size;
			start->x = rand() % (1300 + 100 * start->size) - 50 * start->size;
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