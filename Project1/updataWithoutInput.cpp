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
	int x;
	int y;
	double rad;
	int speed;
	int size;
	int attack;
	int hit;
	struct bulletchain* next;
};
void updateList(item** head, int* count);
void inititem(item* start);//初始化单个陨石
void updataWithoutInput(bulletchain* bullet, item* oxygen, item* carbon, item* iron, item* silicon, item* rubbish, 
	int* oxygennumber,int* carbonnumber, int* ironnumber, int* siliconnumber, int* rubbishnumber, int* oxygengain,
	int* carbongain,int* irongain, int* silicongain, char exception[]) {
	int a = 0;
	item* tlast = new item();
	while (a < 50) {
		switch(a) {
				case 0:
				tlast = oxygen;
				break;
				case 10:
				tlast = carbon;
				break;
				case 20:
				tlast = iron;
				break;
				case 30:
					tlast = silicon;
					break;
				case 40:
					tlast = rubbish;
					break;
		}
		bulletchain* thisbullet = bullet;
		while (thisbullet) {
			item* last=tlast;
			item* head = last;
			while (last) {
				if (((thisbullet->x + thisbullet->size) > last->x || (thisbullet->x - thisbullet->size) < (last->x + 100 * last->size)) &&
					((thisbullet->y + thisbullet->size) > last->y || (thisbullet->y - thisbullet->size) < (last->y + 100 * last->size))) {
					last->blood -= thisbullet->attack;//陨石扣血
					thisbullet->hit++;
					if (last->blood <= 0) {
						switch (a) {
						case 10:
							*oxygengain += (last->size) * 25;
							*oxygennumber--;
							updateList(&oxygen, oxygennumber);
							break;
						case 20:
							*carbongain += (last->size) * 25;
							*carbonnumber--;
							updateList(&carbon, carbonnumber);
							break;
						case 30:
							*irongain += (last->size) * 25;
							*ironnumber--;
							updateList(&iron,ironnumber);
							break;
						case 40:
							*silicongain += (last->size) * 25;
							*siliconnumber--;
							updateList(&silicon, siliconnumber);
							break;
						case 50:*rubbishnumber--; updateList(&rubbish, rubbishnumber); break;
						}//计算材料捕获数，减少陨石总量
						if (last == head) {
							last = last->next;
							free(head);
							tlast = last;
							head = last;
						}
						else {
							last = last->next;
							free(head->next);
							head->next = last;
						}//删除空血量陨石
					}
					else {
						if (last != head) {
							head = head->next;
						}
						last = last->next;
					}
				}//判定受击陨石
			}
			thisbullet = thisbullet->next;
			delete(last);
			delete(head);
		}
		a += 10;
		
	}//判定受击陨石，陨石扣血，删除空血量陨石，计算材料捕获数，减少陨石总量
	bulletchain* thisbullet = bullet;
	bulletchain* headbullet = thisbullet;
	delete(tlast);
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
void updateList(item** head, int* count) {
	item* curr = *head;
	item* prev = NULL;
	while (curr) {
		curr->x += curr->speedx;
		curr->y += curr->speedy;
		// 边界检查
		if (curr->x < -200 || curr->x > 1500 || curr->y < -200 || curr->y > 900) {
			item* tmp = curr;
			if (prev == NULL) *head = curr->next;
			else prev->next = curr->next;
			curr = curr->next;
			delete tmp; // 释放内存
			if (count) (*count)--;
		}
		else {
			prev = curr;
			curr = curr->next;
		}
	}
}