#define _CRT_SECURE_NO_WARNINGS
#include <graphics.h>  
#include <stdio.h>
#include<conio.h>
#pragma comment(lib, "MSIMG32.LIB")
void putimage_a(int x, int y, IMAGE* pImg);

void login() {
    IMAGE cover, Login;
    loadimage(&cover, _T("D:\\game\\pack\\login\\cover.png"), 1300, 700);
    loadimage(&Login, _T("D:\\game\\pack\\login\\start.png"), 400, 160);
    putimage(0, 0, &cover);
    putimage_a(450, 500, &Login);
    ExMessage m;
    setbkmode(TRANSPARENT);
    while (1) {
        if (peekmessage(&m, EX_MOUSE)) {
            if (m.x > 450 && m.x < 850 && m.y>500 && m.y < 660 && m.message == WM_LBUTTONDOWN) {
                Resize(&Login, 600, 400);
                loadimage(&Login, _T("D:\\game\\pack\\login\\Window.png"), 600, 400);
                cleardevice();
                putimage(0, 0, &cover);
                putimage(350, 150, &Login);
                break;
            }

        }
    }
    IMAGE regbut, logbut, pass, name;
    loadimage(&pass, _T("D:\\game\\pack\\login\\text.png"), 450, 50);
    loadimage(&name, _T("D:\\game\\pack\\login\\text.png"), 450, 50);
    loadimage(&regbut, _T("D:\\game\\pack\\login\\regis.png"), 150, 60);
    loadimage(&logbut, _T("D:\\game\\pack\\login\\login.png"), 150, 60);
    putimage(425, 275, &name);
    putimage(425, 350, &pass);
    putimage(450, 440, &logbut);
    putimage(700, 440, &regbut);
    wchar_t namest[15];
    wchar_t passst[16];
    char ch;
    int a = 0, b = 0;
    namest[0] = '\0';
    passst[0] = '\0';
    settextstyle(25, 0, _T("Consolas"));
    IMAGE namebk, passbk, textcover;
    getimage(&textcover, 0, 650, 600, 700);
    while (1) {
        if (peekmessage(&m, EX_MOUSE)) {
            if (m.message == WM_LBUTTONDOWN) {
                putimage(0, 650, &textcover);
                if (m.x > 425 && m.x < 875 && m.y>275 && m.y < 325) {
                    settextstyle(25, 0, _T("Consolas"));
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
                            outtextxy(450, 287, namest);
                        }
                        if (peekmessage(&m, EX_MOUSE) && m.message == WM_LBUTTONDOWN && !(m.x > 425 && m.x < 875 && m.y>275 && m.y < 325)) {
                            break;
                        }
                    }
                }//用户名
                if (m.x > 425 && m.x < 875 && m.y>350 && m.y < 400) {
                    settextstyle(25, 0, _T("Consolas"));
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
                            outtextxy(450, 362, star);
                        }
                        if (peekmessage(&m, EX_MOUSE) && m.message == WM_LBUTTONDOWN && !(m.x > 425 && m.x < 875 && m.y>350 && m.y < 400)) {
                            break;
                        }
                    }
                }//密码
                if (m.x > 450 && m.x < 600 && m.y>440 && m.y < 500) {
                    settextstyle(50, 0, _T("Consolas"));
                    FILE* fp = NULL;
                    int enter = 1;
                    char correct[16];
                    if ((fp = fopen("D:\\game\\txt\\name1.txt", "r")) == NULL) {
                        outtextxy(0, 650, L"出错");
                        enter = 2;
                    }
                    else {
                        fgets(&correct[0], 16, fp);
                        for (int a = 0; correct[a] != '\0' && namest[a] != '\0'; a++) {
                            if (correct[a] != namest[a]) {
                                enter = 0;
                                break;
                            }
                        }
                    }
                    if ((fp = fopen("D:\\game\\txt\\pass1.txt", "r")) == NULL) {
                        outtextxy(0, 650, L"出错");
                        enter = 2;
                    }
                    else {
                        fgets(&correct[0], 16, fp);
                        if (passst[0] == '\0' || namest[0] == '\0') enter = 0;
                        for (int a = 0; correct[a] != '\0' && passst[a] != '\0'; a++) {
                            if (correct[a] != passst[a]) {
                                enter = 0;
                                break;
                            }
                        }
                    }
                    if (enter == 0) {
                        outtextxy(0, 650, L"用户名或密码有误");
                    }
                    if (enter == 1) break;
                }//登录
                if (m.x > 700 && m.x < 850 && m.y>440 && m.y < 500) {
                    login();
                    break;
                }
            }
        }
    }
    return;
}
