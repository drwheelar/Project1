#define _CRT_SECURE_NO_WARNINGS
#include <graphics.h>  
#include <stdio.h>
#include<conio.h>
#pragma comment(lib, "MSIMG32.LIB")
void putimage_a(int x, int y, IMAGE* pImg);
void GetTransparentImage(IMAGE* img,  int x1, int y1, int x2, int y2);
void premultiply(IMAGE* pImg);
IMAGE* drawrubbish() {
    IMAGE* rubbish = new IMAGE(500, 300);
    DWORD* pRubbishBuf = GetImageBuffer(rubbish);
    for (int i = 0; i < 500 * 300; i++) {
        pRubbishBuf[i] = 0x00000000;
    }
    IMAGE* cover = new IMAGE();
    loadimage(cover, _T("D:\\game\\pack\\drawrubbish\\back.png"), 1300, 700);
    if (cover->getwidth() == 0) {
        outtextxy(0, 0, L" 加载失败");
        delete cover;
        while (1) {};
    }
    premultiply(cover);
    ExMessage m;
    setlinecolor(WHITE);
    setfillcolor(WHITE);
    int a = 0;
    char c = NULL;
    while (1) {
        peekmessage(&m, EX_MOUSE);
        if (m.message == WM_LBUTTONDOWN) { a = 1; }
        if (m.message == WM_LBUTTONUP) { a = 0; }
        if (_kbhit()) {
            c = _getch();
            if (c == 'r' || c == 'R') {
                for (int i = 0; i < 500 * 300; i++) pRubbishBuf[i] = 0x00000000;
                c = 0;
            }
        }
        if (m.x > 450 && m.x < 950 && m.y>100 && m.y < 400) {
            if (a == 1) {
                SetWorkingImage(rubbish);
                setlinecolor(WHITE);
                setfillcolor(WHITE);
                fillcircle(m.x - 450, m.y - 100, 7);
                for (int i = 0; i < 500 * 300; i++) {
                    if (pRubbishBuf[i] != 0x00000000) {
                        pRubbishBuf[i] |= 0xFF000000;
                    }
                }
                SetWorkingImage(NULL);
            }
        }
        BeginBatchDraw();
        cleardevice();
        putimage_a(0, 0, cover);  
        putimage_a(450, 100, rubbish); 
        EndBatchDraw();
        if (c == 13) {
            delete cover;
            premultiply(rubbish);
            return rubbish;
        }
    }
}
void premultiply(IMAGE* pImg) {
    DWORD* p = GetImageBuffer(pImg);
    int total = pImg->getwidth() * pImg->getheight();
    for (int i = 0; i < total; i++) {
        BYTE a = (p[i] >> 24) & 0xFF;
        BYTE r = (p[i] >> 16) & 0xFF;
        BYTE g = (p[i] >> 8) & 0xFF;
        BYTE b = (p[i]) & 0xFF;
        r = (BYTE)((DWORD)r * a / 255);
        g = (BYTE)((DWORD)g * a / 255);
        b = (BYTE)((DWORD)b * a / 255);
        p[i] = (a << 24) | (r << 16) | (g << 8) | b;
    }
}