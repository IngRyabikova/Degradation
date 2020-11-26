#pragma once
#include "TXLib.h"

//Размер места
const int PLACE_SIZE = 50;

struct Objects
{
    int x;
    int y;
};

struct Plan
{
    int schirina;
    int visota;
    int x;
    int y;
    HDC pic;
    int N_MEST;
    Objects mesto[100];
};

int urovni = 1;
Plan plans[2];
int N_MEST = 900;
Objects mesto [180];
Objects stol_ychitela [1];
Objects doska [1];

//Рисование столов в режиме разработчика (Да, комменты к функциям нужны)
bool dev_mode(Objects* mesto, bool showDebug)
{
    if(GetAsyncKeyState(VK_TAB) &&  GetAsyncKeyState(VK_SPACE))
    {
        showDebug = !showDebug;
        txSleep(200);
    }

    if (showDebug)
    {
        //Их разве всегда 8???
        for (int nomer = 0; nomer < N_MEST; nomer++)   // телепорт на парту
        {
            txSetFillColor(TX_RED);
            txRectangle (mesto[nomer].x, mesto[nomer].y, mesto[nomer].x + PLACE_SIZE, mesto[nomer].y + PLACE_SIZE);
        }





        //Вывод координат на экран
        char strx[5000];
        char stry[5000];
        sprintf(strx, "Координата х: %d ", txMouseX());
        sprintf(stry, "Координата y: %d ", txMouseY());
        txSetColor(TX_WHITE);
        txDrawText(955,501,1158,556,strx);
        txDrawText(958,585,1161,639,stry);
    }

    return showDebug;
}

HDC smena_classa(HDC pic, Objects* mesto, int* n_pics, int uroven_otstalosti)
{
    for (int i = 0; i < urovni; i++)
    {
        Win32::TransparentBlt (txDC(), 730 + 120 * i, 450, 100, 130, plans[i].pic, 0, 0, plans[i].schirina, plans[i].visota, TX_RED);

        if (txMouseX() >= 730 + 120 * i && txMouseY() >= 450 &&
            txMouseX() <= 830 + 120 * i && txMouseY() <= 580 &&
            txMouseButtons()== 1)
        {
            //Всех учеников удаляем
            *n_pics = 0;

            pic = plans[i].pic;

            N_MEST = plans[i].N_MEST;
            for (int v = 0; v < plans[i].N_MEST; v++)
            {
                mesto[v] = plans[i].mesto[v];
            }
        }
    }

    //Уровень деградации
    if (uroven_otstalosti >= 100)
    {
        urovni = urovni++;
        if (urovni > 2)
            urovni = 2;
    }

    return pic;
}
