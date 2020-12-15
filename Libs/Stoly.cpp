///\file Stoly.cpp
#pragma once
#include "TXLib.h"

///������ ����� �� �����
const int PLACE_SIZE = 50;
/// ��������� "�����"
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
/// �� ��������� �������� �������� ������
int openedLevels = 1;
Plan plans[30];
int N_MEST = 900;
Objects mesto [180];



///��������� ������ � ������ ������������
bool dev_mode(Objects* mesto, bool showDebug)
{
    if(GetAsyncKeyState(VK_TAB) &&  GetAsyncKeyState(VK_SPACE))
    {
        showDebug = !showDebug;
        txSleep(200);
    }

    if (showDebug)
    {
        //�� ����� ������ 8???
        for (int nomer = 0; nomer < N_MEST; nomer++)   // �������� �� �����
        {
            txSetFillColor(TX_RED);
            txRectangle (mesto[nomer].x, mesto[nomer].y, mesto[nomer].x + PLACE_SIZE, mesto[nomer].y + PLACE_SIZE);
        }





        //����� ��������� �� �����
        char strx[5000];
        char stry[5000];
        sprintf(strx, "���������� �: %d ", txMouseX());
        sprintf(stry, "���������� y: %d ", txMouseY());
        txSetColor(TX_WHITE);
        txDrawText(955,501,1158,556,strx);
        txDrawText(958,585,1161,639,stry);
    }

    return showDebug;
}
/// ����� ������(����)
HDC smena_classa(HDC pic, Objects* mesto, int* n_pics, int uroven_otstalosti)
{
    txSelectFont("Arial", 30, 10, true);
    txDrawText(700, 500, 850, 530, "������ �����");

    for (int i = 0; i < openedLevels; i++)
    {
        Win32::TransparentBlt (txDC(), 715 + 120 * i, 530, 100, 130, plans[i].pic, 0, 0, plans[i].schirina, plans[i].visota, TX_RED);

        if (txMouseX() >= 715 + 120 * i && txMouseY() >= 530 &&
            txMouseX() <= 830 + 120 * i && txMouseY() <= 660 &&
            txMouseButtons()== 1)
        {
            //���� �������� ������� ��� ����� ������
            *n_pics = 0;

            pic = plans[i].pic;

            N_MEST = plans[i].N_MEST;
            for (int v = 0; v < plans[i].N_MEST; v++)
            {
                mesto[v] = plans[i].mesto[v];
            }
        }
    }

    //������� ����������
    if (uroven_otstalosti >= 100 && openedLevels == 1)
    {
        openedLevels = 2;
    }
    if (uroven_otstalosti >= 200 && openedLevels == 2)
    {
        openedLevels = 3;
    }

    if (openedLevels > 3)
        openedLevels = 3;

    return pic;
}
