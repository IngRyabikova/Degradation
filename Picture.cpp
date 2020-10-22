#include "Lib/TXLib.h"
const char* active_category;

struct Picture
{
    int x;
    int y;
    const char* adres;
    bool visible;
    const char* category;
    int otstalost;
    HDC pic;
    int width;
    int height;
};
void drawkrugbutton(int x, int y, int x1, int y1, const char* text)
{
    Win32::RoundRect(txDC(), x,y,x1,y1, 50, 50);
    txDrawText (x,y,x1,y1, text);
}
void drawkrugbutton(int x, int y,const char* text)
{
    drawkrugbutton(x, y, x + 160, y + 60, text);
}
//��������� ��������� ��������/��������
void draw_variants(Picture* variants, int N_VARS, const char* active_category)
{
    for (int nomer = 0; nomer < N_VARS; nomer = nomer + 1)
    {
        if (variants[nomer].category == active_category){
            Win32::TransparentBlt (txDC(), variants[nomer].x,   variants[nomer].y, 100, 100, variants[nomer].pic, 0, 0, variants[nomer].width, variants[nomer].height, TX_WHITE);
        }
    }
}

//�������� �������� ��������
void dvizhenie(Picture* centr, int speed_x, int speed_y, int n_active)
{
    if(GetAsyncKeyState(VK_LEFT) && centr[n_active].visible)
    {
        centr[n_active].x = centr[n_active].x  -speed_x;
    }

    if(GetAsyncKeyState(VK_RIGHT) && centr[n_active].visible)
    {
        centr[n_active].x = centr[n_active].x  +speed_x;
    }

    if(GetAsyncKeyState(VK_UP) && centr[n_active].visible )
    {
        centr[n_active].y = centr[n_active].y  -speed_y;
    }

    if(GetAsyncKeyState(VK_DOWN) && centr[n_active].visible  )
    {
        centr[n_active].y = centr[n_active].y  +speed_y;
    }
}

//�������� ��������
void del_pic (Picture* centr, int n_pics, Picture* variants, int N_VARS, HDC pic1)
{
    for (int nomer = 0; nomer < N_VARS; nomer = nomer + 1)
    {
        txDeleteDC(variants[nomer].pic);
    }

    for(int nomer = 0; nomer < n_pics; nomer = nomer + 1)
    {
        txDeleteDC(centr[nomer].pic);
    }

    txDeleteDC(pic1);

}


int select_active(Picture* centr, int n_pics, int pic_width, int pic_height, int n_active)
{
    for (int nomer = 0; nomer < n_pics; nomer = nomer + 1)   // ����������� ��������� ���������
    {
        if (txMouseX() >= centr[nomer].x &&
           txMouseY() >= centr[nomer].y &&
           txMouseX() <= centr[nomer].x + pic_width  &&
           txMouseY() <= centr[nomer].y + pic_height &&
           txMouseButtons()== 1)
        {
            n_active = nomer;
        }
    }

    return n_active;
}

void draw_centr_pic(Picture* centr, int n_pics, int pic_width, int pic_height)
{
    for (int nomer = 0; nomer < n_pics; nomer = nomer + 1)
    {
        if (centr[nomer].visible)
        {
            Win32::TransparentBlt (txDC(), centr[nomer].x,   centr[nomer].y, pic_width, pic_height, centr[nomer].pic, 0, 0, centr[nomer].width, centr[nomer].height, TX_WHITE);
        }
    }
}

int newCenterPic(Picture* variants, Picture* centr, int N_VARS, int n_pics, int n_active)
{
    for (int nomer = 0; nomer < N_VARS; nomer = nomer + 1)
    {
        if (txMouseX() >= variants[nomer].x &&
           txMouseY() >= variants[nomer].y &&
           txMouseX() <= variants[nomer].x + 100 &&
           txMouseY() <= variants[nomer].y + 100 &&
           txMouseButtons() == 1 && variants[nomer].category == active_category)
        {
            //����������� ����� ����������� ��������
            centr[n_pics] = {458, 608, variants[nomer].adres, true, active_category, variants[nomer].otstalost,
                            variants[nomer].pic, variants[nomer].width, variants[nomer].height};
            n_pics++;
            txSleep(100);
        }
    }

    return n_pics;
}

int deleteCenterPic(Picture* centr, int n_pics, int n_active)
{
    if (GetAsyncKeyState(VK_DELETE))
    {
        if(n_pics>0)
        {
            n_pics--;
            centr[n_active].x = centr[n_pics].x;
            centr[n_active].y = centr[n_pics].y;
            centr[n_active].pic = centr[n_pics].pic;
            txSleep(100);
        }
    }

    return n_pics;
}


//������� ��� �������� � ������
int del_all (int n_pics)
{
    txSetFillColour(TX_WHITE);
    drawkrugbutton(1021,27,1234,92,"������� ���!");
    if (txMouseX() >= 1021 &&
       txMouseY() >= 27 &&
       txMouseX() <= 1234 &&
       txMouseY() <= 92 &&
       txMouseButtons() == 1 )
    {
       n_pics = 0;
    }

    return n_pics;
}