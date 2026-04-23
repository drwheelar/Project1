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
void init(item** head, int num); 
void inititem(item* start);//初始化单个陨石
void updataWithoutInput(bulletchain** bullet, item** oxygen, item** carbon, item** iron, item** silicon, item** rubbish,
	int* oxygennumber, int* carbonnumber, int* ironnumber, int* siliconnumber, int* rubbishnumber, int* oxygengain,
	int* carbongain, int* irongain, int* silicongain, char exception[]) {
	int a = 0;
	item** tlast = new item * ();
	while (a < 50) {
		switch (a) {
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
		if (tlast == NULL) {
			a += 10; continue;
		}
		if (a == 30) {
			a += 10; continue;
		}
		bulletchain* thisbullet = *bullet;
		while (thisbullet) {
			item* last = *tlast;
			item* head = last;
			while (last) {
				if (((thisbullet->x + thisbullet->size) > last->x && (thisbullet->x - thisbullet->size) < (last->x + 30 * last->size)) &&
					((thisbullet->y + thisbullet->size) > last->y && (thisbullet->y - thisbullet->size) < (last->y + 30 * last->size))) {
					last->blood -= thisbullet->attack;//陨石扣血
					thisbullet->hit++;
						switch (a) {
						case 10:
							*oxygengain += (last->size) * 25;
							//*oxygennumber--;
							break;
						case 20:
							*carbongain += (last->size) * 25;
							//*carbonnumber--;
							break;
						case 30:
							*irongain += (last->size) * 25;
							//*ironnumber--;
							break;
						case 40:
							*silicongain += (last->size) * 25;
							//*siliconnumber--;
							break;
						case 50://*rubbishnumber--; 
							break;
						}//计算材料捕获数，减少陨石总量
						if (last->blood <= 0) {
							if (last == head) {
								last = last->next;
								free(head);
								*tlast = last;
								head = last;
							}
							else {
								last = last->next;
								free(head->next);
								head->next = last;
							}//删除空血量陨石
						}
				}//判定受击陨石
				if (!last) break;
				last = last->next;
			}
			thisbullet = thisbullet->next;
		}
		a += 10;

	}//判定受击陨石，陨石扣血，删除空血量陨石，计算材料捕获数，减少陨石总量
	updateList(oxygen, oxygennumber);
	updateList(carbon, carbonnumber);
	updateList(iron, ironnumber);
	updateList(silicon, siliconnumber);
	updateList(rubbish, rubbishnumber);
	bulletchain* thisbullet = *bullet;
	bulletchain* headbullet = thisbullet;
	//delete(tlast);
	while (thisbullet) {
		if (thisbullet->hit > 0) {
			if (thisbullet == *bullet) {
				*bullet = (*bullet)->next;
				thisbullet = *bullet;
				headbullet = *bullet;
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
	thisbullet = *bullet;
	while (thisbullet) {
		double a = cos(thisbullet->rad);
		thisbullet->x += thisbullet->speed * sin(thisbullet->rad);
		thisbullet->y -= thisbullet->speed * cos(thisbullet->rad);
		thisbullet = thisbullet->next;
	}
	thisbullet = *bullet;
	headbullet = NULL;
	while (thisbullet) {
		if (thisbullet->x > 1300 || thisbullet->x < -thisbullet->size || thisbullet->y < -thisbullet->size || thisbullet->y>700) {
			if (headbullet) {
				headbullet->next = thisbullet->next;
				thisbullet = thisbullet->next;
			}
			else {
				thisbullet = thisbullet->next;
				*bullet = thisbullet;
			}
		}
		else {
			if (headbullet) {
				headbullet = headbullet->next;
				thisbullet = thisbullet->next;
			}
			else {
				thisbullet = thisbullet->next;
				headbullet = *bullet;
			}
		}
		if (*ironnumber < 5 && strcmp(exception, "iron") != 0) {
			/*srand((unsigned)time(NULL));
			int num = rand() % 2 + 1;
			if (num == 1) {*/
			int a = 10 - *carbonnumber;
			item* last = *iron;
			while (last->next) last = last->next;
			for (; a > 0; a--) {
				last->next = new item();
				inititem(last->next);
				//(*ironnumber)++;
				last = last->next;
			}
		}
		if (*oxygennumber < 5 && strcmp(exception, "oxygen") != 0) {
			int a = 10 - *carbonnumber;
				item* last = *oxygen;
				while (last->next) last = last->next;			
				for (; a > 0; a--) {
				last->next = new item();
				inititem(last->next);
				//(*oxygennumber)++;
				last = last->next;
			}

		}
		if (*siliconnumber < 5 && strcmp(exception, "silicon") != 0) {
			int a = 10 - *carbonnumber;				
			item* last = *silicon;
			while (last->next) last = last->next;
			for (; a > 0; a--) {
				last->next = new item();
				inititem(last->next);
				//(*siliconnumber)++;
				last = last->next;
			}
		}
		if (*carbonnumber < 5 && strcmp(exception, "carbon") != 0) {
			int a = 10 - *carbonnumber;
			item* last = *carbon;
			while (last->next) last = last->next;
				for (; a > 0; a--) {
					last->next = new item();
					inititem(last->next);
					//(*carbonnumber)++;
					last = last->next;
				}

		}//判定是否增加陨石
	}
}
void updateList(item** head, int* count) {
	//if (*head = NULL) init(head, 5);
	item* curr = *head;
	item* prev = NULL;
	while (curr) {
		curr->x += curr->speedx;
		curr->y += curr->speedy;
		// 边界检查
		if (curr->x < -150 || curr->x > 1300 || curr->y < -150 || curr->y > 700) {
			item* tmp = curr;
			if (prev == NULL) *head = curr->next;
			else prev->next = curr->next;
			curr = curr->next;
			//delete tmp; // 释放内存
			//if (count)  (*count)--;
		}
		else {
			prev = curr;
			curr = curr->next;
		}
	}
}