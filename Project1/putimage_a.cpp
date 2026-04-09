#define _CRT_SECURE_NO_WARNINGS
#include <graphics.h>  
#include <stdio.h>
#include<conio.h>
#pragma comment(lib, "MSIMG32.LIB")
void putimage_a(int x, int y, IMAGE* pImg) {
    if (pImg == NULL) return;
    int w = pImg->getwidth();
    int h = pImg->getheight();
    if (w == 0 || h == 0) return;
    HDC dstDC = GetImageHDC(NULL);
    HDC srcDC = GetImageHDC(pImg);
    BLENDFUNCTION bf = { AC_SRC_OVER, 0, 255, AC_SRC_ALPHA };
    AlphaBlend(dstDC, x, y, w, h, srcDC, 0, 0, w, h, bf);
}
/*void putimage_a(int x, int y, IMAGE* pImg) {
    int w = pImg->getwidth();
    int h = pImg->getheight();
    HDC dstDC = GetImageHDC(NULL);
    HDC srcDC = GetImageHDC(pImg);
    BLENDFUNCTION bf = { 0 };
    bf.BlendOp = AC_SRC_OVER;
    bf.BlendFlags = 0;
    bf.SourceConstantAlpha = 255;  
    bf.AlphaFormat = AC_SRC_ALPHA;
    AlphaBlend(dstDC, x, y, w, h, srcDC, 0, 0, w, h, bf);
}*/
/*void putimage_a(int x, int y, IMAGE* pImg) {
    HDC dstDC = GetImageHDC(NULL);
    HDC srcDC = GetImageHDC(pImg);
    int w = pImg->getwidth();
    int h = pImg->getheight();
    BLENDFUNCTION blendFn = { AC_SRC_OVER, 0, 255, AC_SRC_ALPHA };
    AlphaBlend(dstDC, x, y, w, h, srcDC, 0, 0, w, h, blendFn);
}*/