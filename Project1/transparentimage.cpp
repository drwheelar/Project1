#define _CRT_SECURE_NO_WARNINGS
#include <graphics.h>  
#include <stdio.h>
#include<conio.h>
#pragma comment(lib, "MSIMG32.LIB")
void putimage_a(int x, int y, IMAGE* pImg); 
/*void GetTransparentImage(IMAGE* img, int x1, int y1, int x2, int y2)
{
    int w = x2 - x1;
    int h = y2 - y1;
    Resize(img, w, h);
    DWORD* pDest = GetImageBuffer(img);
    DWORD* pSrc = GetImageBuffer();
    for (int y = 0; y < h; y++)
    {
        for (int x = 0; x < w; x++)
        {
            int sx = x1 + x;
            int sy = y1 + y;
            if (sx >= 0 && sx < getwidth() && sy >= 0 && sy < getheight()) {
                pDest[y * w + x] = pSrc[sy * getwidth() + sx];
            }
            else {
                pDest[y * w + x] = 0x00000000;
            }
        }
    }
}*/
void GetTransparentImage(IMAGE* img, int x1, int y1, int x2, int y2)
{
    int w = x2 - x1;
    int h = y2 - y1;
    Resize(img, w, h);
    DWORD* pDest = GetImageBuffer(img);
    DWORD* pSrc = GetImageBuffer();
    int    srcW = getwidth();
    int    srcH = getheight();
    for (int y = 0; y < h; y++)
    {
        for (int x = 0; x < w; x++)
        {
            int sx = x1 + x;
            int sy = y1 + y;
            if (sx >= 0 && sx < getwidth() && sy >= 0 && sy < getheight()) {
                DWORD px = pSrc[sy * srcW + sx];
                pDest[y * w + x] = px | 0xFF000000;
            }
            else{
                pDest[y * w + x] = 0x00000000; 
            }
        }
    }
}