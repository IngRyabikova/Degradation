///\file Stoly.cpp
#pragma once
#include "TXLib.h"

///Размер места на парте
const int PLACE_SIZE = 50;
/// Структура "парта"
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
/// По умолчанию открытые варианты класса
int openedLevels = 1;
Plan plans[30];
int N_MEST = 900;
Objects mesto [180];



///Рисование столов в режиме разработчика
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
/// смена класса(фона)
HDC smena_classa(HDC pic, Objects* mesto, int* n_pics, int uroven_otstalosti)
{
    txSelectFont("Arial", 30, 10, true);
    txDrawText(700, 500, 850, 530, "Выбери класс");

    for (int i = 0; i < openedLevels; i++)
    {
        Win32::TransparentBlt (txDC(), 715 + 120 * i, 530, 100, 130, plans[i].pic, 0, 0, plans[i].schirina, plans[i].visota, TX_RED);

        if (txMouseX() >= 715 + 120 * i && txMouseY() >= 530 &&
            txMouseX() <= 830 + 120 * i && txMouseY() <= 660 &&
            txMouseButtons()== 1)
        {
            //Всех учеников удаляем при смене класса
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
        openedLevels++;
        if (openedLevels > 3)
            openedLevels = 3;
    }

    return pic;
}
