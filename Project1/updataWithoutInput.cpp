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
void createlist(item** itemlist, int* number);
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
		if (a == 30&&strcmp(exception,"silicon")==0) {
			a += 10; continue;
		}
		bulletchain* thisbullet = *bullet;
		while (thisbullet) {
			item* last = *tlast;
			item* head = last;
			while (last) {
				if (((thisbullet->x + thisbullet->size) > last->x && (thisbullet->x - thisbullet->size) < (last->x + 50 * last->size)) &&
					((thisbullet->y + thisbullet->size) > last->y && (thisbullet->y - thisbullet->size) < (last->y + 50 * last->size))) {
					last->blood -= thisbullet->attack;//陨石扣血
					thisbullet->hit++;
					if (last->blood <= 0) {
						switch (a) {
						case 0:
							(*oxygengain) += (last->size) * 25;
							(*oxygennumber)--;
							break;
						case 10:
							(*carbongain) += (last->size) * 25;
							(*carbonnumber)--;
							break;
						case 20:
							(*irongain) += (last->size) * 25;
							(*ironnumber)--;
							break;
						case 30:
							(*silicongain) += (last->size) * 25;
							(*siliconnumber)--;
							break;
						case 40:(*rubbishnumber)--;
							break;
						}//计算材料捕获数，减少陨石总量
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
				if (last != head) head = head->next;
				last = last->next;
				if (!last) break;
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
	}
	if (*ironnumber < 5 && strcmp(exception, "iron") != 0) {
		/*srand((unsigned)time(NULL));
		int num = rand() % 2 + 1;
		if (num == 1) {*/
		createlist(iron, ironnumber);
	}
	if (*oxygennumber < 5 && strcmp(exception, "oxygen") != 0) {
		createlist(oxygen, oxygennumber);

	}
	if (*siliconnumber < 5 && strcmp(exception, "silicon") != 0) {
		createlist(silicon, siliconnumber);
	}
	if (*carbonnumber < 5 && strcmp(exception, "carbon") != 0) {
		createlist(carbon, carbonnumber);
	}//判定是否增加陨石
	createlist(rubbish, rubbishnumber);
 }
void updateList(item** head, int* count) {
	if (*head == NULL) return; 
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
			(*count)--;
		}
		else {
			prev = curr;
			curr = curr->next;
		}
	}
}
void createlist(item** itemlist,int*number){
	/*srand((unsigned)time(NULL));
	int num = rand() % 2 + 1;
	if (num == 1) {*/
	if (*itemlist==NULL) {
		init(itemlist, 5);
		*number = 5;
		return;
	}
	int a = 5 - *number;
	item* last = *itemlist;
	while (last->next) last = last->next;
	for (; a > 0; a--) {
		last->next = new item();
		srand((unsigned)clock());
		inititem(last->next);
		(*number)++;
		last = last->next;
	}
}