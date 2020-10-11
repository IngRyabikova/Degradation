#include "Lib/TXLib.h"

struct Picture
{
    int x;
    int y;
    int width;
    int height;
    HDC pic;
    bool visible;
    const char* category;
};

//Рисование вариантов учеников/учителей
void draw_variants(Picture* variants, int N_VARS, const char* active_category)
{
    for (int nomer = 0; nomer < N_VARS; nomer = nomer + 1)
    {
        if (variants[nomer].category == active_category){
            Win32::TransparentBlt (txDC(), variants[nomer].x,   variants[nomer].y, 100, 100, variants[nomer].pic, 0, 0, variants[nomer].width, variants[nomer].height, TX_WHITE);
        }
    }
}

//Движение активной картинки
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

//Удаление картинок
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

