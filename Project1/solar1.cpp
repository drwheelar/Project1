#define _CRT_SECURE_NO_WARNINGS
#include <graphics.h>  
#include <stdio.h>
#include <stdlib.h>
#include<conio.h>
#include <time.h>
#pragma comment(lib, "MSIMG32.LIB")
void putimage_a(int x, int y, IMAGE* pImg);
typedef struct item{
	int speedx;
	int speedy;
	int x;
	int y;
	int blood;
	int motion;
	int size;
	struct item* next;
};
void solar1(IMAGE* rubbishpic){
	IMAGE* cover = new IMAGE();
	loadimage(cover, _T("D:\\game\\pack\\solar1\\back\\back.png"), 1300, 700);
	putimage(0, 0, cover );
	item* oxygen= (item*)malloc(sizeof(item));
	item* carbon = (item*)malloc(sizeof(item));
	item* iron = (item*)malloc(sizeof(item));
	item* rubbish = (item*)malloc(sizeof(item));
	item* last = oxygen;
	for (int i = 0; i < 5; i++) {
		item* s = (item*)malloc(sizeof(item));
		last->next = s;
		s->next = NULL;
		srand((unsigned)time(NULL));
		last->size = rand() % 3 + 1;
		last->blood = last->size * 100;
		int a= rand() % 4;
		if (a == 0) {
			last->x = -50*last->size;
			last->y = rand() % (700+100*last->size)-50*last->size;
			last->motion = 1;
		}
		last = last->next;
	}
}