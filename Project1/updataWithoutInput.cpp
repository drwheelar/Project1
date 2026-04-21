#define _CRT_SECURE_NO_WARNINGS
#include <graphics.h>  
#include <stdio.h>
#include <stdlib.h>
#include<conio.h>
#include <time.h>
#include<math.h>
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
void inititem(item* start);//初始化单个陨石
void updataWithoutInput(bulletchain* bullet, item* oxygen, item* carbon, item* iron, item* silicon, item* rubbish, int* oxygennumber,
	int* carbonnumber, int* ironnumber, int* siliconnumber, int* rubbishnumber, int* oxygengain, int* carbongain,
	int* irongain, int* silicongain, char exception[]) {
	int a = 0;
	while (a < 50) {
		item* tlast = new item();
		if (a == 40) {
			tlast = rubbish;
			a = 50;
		}
		if (a == 30 && exception == "silicon") {
			tlast = rubbish;
			a = 50;
		}
		if (a == 30 && exception != "silicon") {
			tlast = silicon;
			a = 40;
		}
		if (a == 20 && exception == "iron") {
			tlast = silicon;
			a = 40;
		}
		if (a == 20 && exception != "iron") {
			tlast = iron;
			a = 30;
		}
		if (a == 10 && exception == "carbon") {
			tlast = iron;
			a = 30;
		}
		if (a == 10 && exception != "carbon") {
			tlast = carbon;
			a = 20;
		}
		if (a == 0 && exception == "oxygen") {
			tlast = carbon;
			a = 20;
		}
		if (a == 0 && exception != "oxygen") {
			tlast = oxygen;
			a = 10;
		}
		bulletchain* thisbullet = bullet;
		while (thisbullet) {
			item* last=tlast;
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
							*oxygengain += (rlast->size) * 25;
							*oxygennumber--;
							break;
						case 20:
							*carbongain += (rlast->size) * 25;
							*carbonnumber--;
							break;
						case 30:
							*irongain += (rlast->size) * 25;
							*ironnumber--;
							break;
						case 40:
							*silicongain += (rlast->size) * 25;
							*siliconnumber--;
							break;
						case 50:*rubbishnumber--; break;
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
			delete(last);
		}
		item* last = rlast;
	}//判定受击陨石，陨石扣血，删除空血量陨石，计算材料捕获数，减少陨石总量
	bulletchain* thisbullet = bullet;
	bulletchain* headbullet = thisbullet;
	while (thisbullet) {
		if (thisbullet->hit > 0) {
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
	if (*ironnumber < 10 && exception != "iron") {
		srand((unsigned)time(NULL));
		int num = rand() % 50 + 1;
		if (num == 1) {
			item* last = iron;
			while (last->next) last = last->next;
			inititem(last->next);
			*ironnumber++;
		}
	}
	if (*oxygennumber < 10 && exception != "oxygen") {
		srand((unsigned)time(NULL));
		int num = rand() % 50 + 1;
		if (num == 1) {
			item* last = oxygen;
			while (last->next) last = last->next;
			inititem(last->next);
			*oxygennumber++;
		}
	}
	if (*siliconnumber < 10 && exception != "silicon") {
		srand((unsigned)time(NULL));
		int num = rand() % 50 + 1;
		if (num == 1) {
			item* last = silicon;
			while (last->next) last = last->next;
			inititem(last->next);
			*siliconnumber++;
		}
	}
	if (*carbonnumber < 10 && exception != "carbon") {
		srand((unsigned)time(NULL));
		int num = rand() % 50 + 1;
		if (num == 1) {
			item* last = carbon;
			while (last->next) last = last->next;
			inititem(last->next);
			*carbonnumber++;
		}
	}//判定是否增加陨石
}