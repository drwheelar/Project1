#define _CRT_SECURE_NO_WARNINGS
#include <graphics.h>  
#include <stdio.h>
#include<conio.h>
#pragma comment(lib, "MSIMG32.LIB")
void putimage_a(int x, int y, IMAGE* pImg);
bool login() {
    wchar_t namest[15];
    wchar_t passst[16];
    IMAGE cover, Login,Login1,back,back1;
    BeginBatchDraw();
    loadimage(&cover, _T("D:\\game\\pack\\login\\cover.png"), 1300, 700);
    loadimage(&Login, _T("D:\\game\\pack\\login\\play.png"), 200, 200);
    loadimage(&Login1, _T("D:\\game\\pack\\login\\play1.png"), 200, 200);
    putimage(0, 0, &cover); 
    putimage_a(550, 450, &Login);
    FlushBatchDraw();
    EndBatchDraw();
    ExMessage m;
    setbkmode(TRANSPARENT);
    while (1) {
        if (peekmessage(&m, EX_MOUSE)) {
            if (m.message == WM_MOUSEMOVE) {
                if (m.x > 550 && m.x < 750 && m.y>450 && m.y < 650) {
                    putimage_a(550, 450, &Login1);
                }
                else putimage_a(550, 450, &Login);
            }
            if (m.x > 550 && m.x < 750 && m.y>450 && m.y < 650 && m.message == WM_LBUTTONDOWN) {
                Resize(&Login, 600, 400);
                loadimage(&Login, _T("D:\\game\\pack\\login\\Window.png"), 600, 400);
                cleardevice();
                putimage(0, 0, &cover);
                putimage(350, 150, &Login);
                break;
            }

        }
    }
    IMAGE pass,name;
    BeginBatchDraw();
    loadimage(&pass, _T("D:\\game\\pack\\login\\text.png"), 450, 50);
    loadimage(&name, _T("D:\\game\\pack\\login\\text.png"), 450, 50);
    loadimage(&Login, _T("D:\\game\\pack\\login\\yes.png"), 100, 100);
    loadimage(&Login1, _T("D:\\game\\pack\\login\\yes1.png"), 100, 100);
    loadimage(&back, _T("D:\\game\\pack\\login\\close.png"), 100, 100);
    loadimage(&back1, _T("D:\\game\\pack\\login\\close1.png"), 100, 100);
    putimage_a(425, 275, &name);
    putimage_a(425, 350, &pass);
    putimage_a(450, 410, &Login);
    putimage_a(750, 410, &back1);
    FlushBatchDraw();
    EndBatchDraw();
    char ch;
    int a = 0, b = 0;
    namest[0] = '\0';
    passst[0] = '\0';
    IMAGE namebk, passbk, textcover;
    getimage(&textcover, 500, 560, 600, 700);
    settextstyle(25, 0, _T("Consolas")); 
    while (1) {
        BeginBatchDraw();
        peekmessage(&m, EX_MOUSE);
        if (m.x > 450 && m.x < 550 && m.y>410 && m.y < 510)putimage_a(450, 410, &Login1);
        else putimage_a(450, 410, &Login);
        if (m.x > 750 && m.x < 850 && m.y>410 && m.y < 510)putimage_a(750, 410, &back1);
        else putimage_a(750, 410, &back);
        FlushBatchDraw();
        EndBatchDraw();
            if (m.message == WM_LBUTTONDOWN) {
                BeginBatchDraw();
                putimage(500, 560, &textcover);
                FlushBatchDraw();
                EndBatchDraw();
                if (m.x > 425 && m.x < 875 && m.y>275 && m.y < 325) {
                    while (_kbhit()) _getch();
                    while (1) {

                        if (_kbhit()) {
                            ch = _getch();
                            if (((ch >= 'a' && ch <= 'z') || (ch >= '0' && ch <= '9') || (ch >= 'A' && ch <= 'Z')) && a <= 13) {
                                namest[a] = ch;
                                a++;
                                namest[a] = '\0';
                            }
                            if (ch == 8 && a > 0) {
                                namest[a - 1] = '\0';
                                a--;
                            }
                            if (ch == 13) break;
                            putimage(425, 275, &name);
                            settextstyle(25, 0, _T("Consolas"));
                            outtextxy(450, 287, namest);
                        }
                        if (peekmessage(&m, EX_MOUSE) && m.message == WM_LBUTTONDOWN && !(m.x > 425 && m.x < 875 && m.y>275 && m.y < 325)) {
                            break;
                        }
                    }
                }//用户名
                if (m.x > 425 && m.x < 875 && m.y>350 && m.y < 400) {
                    while (_kbhit()) _getch();
                    while (1) {
                        clearrectangle(700, 600, 850, 660);
                        if (_kbhit()) {
                            ch = _getch();
                            if (((ch >= 'a' && ch <= 'z') || (ch >= '0' && ch <= '9') || (ch >= 'A' && ch <= 'Z')) && b <= 14) {
                                passst[b] = ch;
                                b++;
                                passst[b] = '\0';
                            }
                            if (ch == 8 && b > 0) {
                                passst[b - 1] = '\0';
                                b--;
                            }
                            if (ch == 13) break;
                            putimage(425, 350, &name);
                            wchar_t star[20];
                            star[0] = '\0';
                            int i = 0;
                            for (; i < b; i++) { star[i] = '*'; }
                            star[i] = '\0';
                            settextstyle(25, 0, _T("Consolas"));
                            outtextxy(450, 362, star);
                        }
                        if (peekmessage(&m, EX_MOUSE) && m.message == WM_LBUTTONDOWN && !(m.x > 425 && m.x < 875 && m.y>350 && m.y < 400)) {
                            break;
                        }
                    }
                }//密码
                if (m.x > 450 && m.x < 550 && m.y>410 && m.y < 510) {
                    FILE* fp = NULL;
                    int enter = 1;
                    char correct[16];
                    if ((fp = fopen("D:\\game\\txt\\name1.txt", "r")) == NULL) {
                        settextstyle(50, 0, _T("微软雅黑"));
                        outtextxy(500, 560, L"出错");
                        enter = 2;
                    }
                    else {
                        fgets(&correct[0], 16, fp);
                        for (int a = 0; correct[a] != '\0' || namest[a] != '\0'; a++) {
                            if (correct[a] != namest[a]) {
                                enter = 0;
                                break;
                            }
                        }
                    }
                    if ((fp = fopen("D:\\game\\txt\\pass1.txt", "r")) == NULL) {
                        settextstyle(50, 0, _T("微软雅黑"));
                        outtextxy(500, 560, L"出错");
                        enter = 2;
                    }
                    else {
                        fgets(&correct[0], 16, fp);
                        if (passst[0] == '\0' || namest[0] == '\0') enter = 0;
                        for (int a = 0; correct[a] != '\0' || passst[a] != '\0'; a++) {
                            if (correct[a] != passst[a]) {
                                enter = 0;
                                break;
                            }
                        }
                    }
                    if (enter == 0) {
                        settextstyle(50, 0, _T("微软雅黑"));
                        outtextxy(500, 560, L"用户名或密码有误");
                    }
                    if (enter == 1) break;
                }//登录
                if (m.x > 750 && m.x < 850 && m.y>410 && m.y < 510) {
                    login();
                    break;
                }
            }
     
    }
    return true;
}
