#define _CRT_SECURE_NO_WARNINGS
#include <graphics.h>  
#include <stdio.h>
#include<conio.h>
#include <stdlib.h>
#include <time.h>
#include<math.h>
void Resize_a(IMAGE* pDestImg, IMAGE* pSrcImg, int destWidth, int destHeight)
{
    if (pDestImg == NULL || pSrcImg == NULL) return;
    if (destWidth <= 0 || destHeight <= 0) return;

    int srcWidth = pSrcImg->getwidth();
    int srcHeight = pSrcImg->getheight();
    if (srcWidth == 0 || srcHeight == 0) return;

    Resize(pDestImg, destWidth, destHeight);

    DWORD* destBuffer = GetImageBuffer(pDestImg);
    DWORD* srcBuffer = GetImageBuffer(pSrcImg);

    for (int y = 0; y < destHeight; y++)
    {
        for (int x = 0; x < destWidth; x++)
        {
            // 直接取整映射
            int srcX = x * srcWidth / destWidth;
            int srcY = y * srcHeight / destHeight;

            // 边界安全
            srcX = max(0, min(srcX, srcWidth - 1));
            srcY = max(0, min(srcY, srcHeight - 1));

            destBuffer[x + y * destWidth] = srcBuffer[srcX + srcY * srcWidth];
        }
    }
}