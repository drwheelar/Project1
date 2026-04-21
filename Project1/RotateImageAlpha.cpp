#define _CRT_SECURE_NO_WARNINGS
#include <graphics.h>  
#include <stdio.h>
#include<conio.h>
#include <stdlib.h>
#include<math.h>
void RotateImageAlpha(
    IMAGE* dst,
    IMAGE* src,
    double radian,
    int px, int py,         // 👈 原图中的旋转定点坐标
    bool autosize = true)
{
    if (!src || !dst) return;

    int w = src->getwidth();
    int h = src->getheight();
    double c = cos(radian);
    double s = sin(radian);

    // 1. 计算新画布尺寸 (如果自动调整)
    int nw = w, nh = h;
    int npx = px, npy = py; // 新图中的旋转轴心位置

    if (autosize) {
        // 计算原图四个角相对于 (px, py) 旋转后的极值，确定边界
        double x1 = -px * c - (-py) * s;
        double y1 = -px * s + (-py) * c;
        double x2 = (w - px) * c - (-py) * s;
        double y2 = (w - px) * s + (-py) * c;
        double x3 = (w - px) * c - (h - py) * s;
        double y3 = (w - px) * s + (h - py) * c;
        double x4 = -px * c - (h - py) * s;
        double y4 = -px * s + (h - py) * c;

        double minX = min(min(x1, x2), min(x3, x4));
        double maxX = max(max(x1, x2), max(x3, x4));
        double minY = min(min(y1, y2), min(y3, y4));
        double maxY = max(max(y1, y2), max(y3, y4));

        nw = (int)(maxX - minX + 0.5);
        nh = (int)(maxY - minY + 0.5);
        npx = (int)(-minX + 0.5); // 旋转点在新画布中的 X 坐标
        npy = (int)(-minY + 0.5); // 旋转点在新画布中的 Y 坐标
    }

    Resize(dst, nw, nh);
    DWORD* pSrc = GetImageBuffer(src);
    DWORD* pDst = GetImageBuffer(dst);

    // 2. 填充新像素
    for (int y = 0; y < nh; y++) {
        for (int x = 0; x < nw; x++) {
            // 目标点相对于新轴心的偏移
            double tx = x - npx;
            double ty = y - npy;

            // 逆向旋转映射回原图 (逆旋转公式)
            // ox = tx * cos(theta) + ty * sin(theta) + px
            // oy = -tx * sin(theta) + ty * cos(theta) + py
            int ox = (int)(tx * c + ty * s + px + 0.5);
            int oy = (int)(-tx * s + ty * c + py + 0.5);

            if (ox >= 0 && ox < w && oy >= 0 && oy < h) {
                pDst[y * nw + x] = pSrc[oy * w + ox];
            }
            else {
                pDst[y * nw + x] = 0x00000000; // 超出范围透明
            }
        }
    }
}