#include "TXLib.h"
struct Objects
{
    int x;
    int y;
};
struct Plan
{
    int x;
    int y;
    HDC pic;
    int N_MEST;
    Objects mesto[10];
};

Plan plans[2];
int N_MEST = 8;
Objects mesto [8];
Objects stol_ychitela [1];

//Рисование столов в режиме разработчика (Да, комменты к функциям нужны)
bool dev_mode(Objects* mesto, bool stat)
{   int x_mouse = txMouseX();
    int y_mouse = txMouseY();
    if(GetAsyncKeyState(VK_TAB) &&  GetAsyncKeyState(VK_SPACE))
    {
        stat = !stat;
        txSleep(200);
    }

    if (stat == true)
    {
        //Их разве всегда 8???
        for (int nomer = 0; nomer < 8; nomer = nomer + 1)   // телепорт на парту
        {
            txSetFillColor(TX_RED);
            txRectangle (mesto[nomer].x, mesto[nomer].y, mesto[nomer].x + 30, mesto[nomer].y + 30);
            txRectangle (stol_ychitela[0].x, stol_ychitela[0].y, stol_ychitela[0].x + 30, stol_ychitela[0].y + 30);
        }
         char strx[5000];
        char stry[5000];
    sprintf(strx, "Координата х: %d ", x_mouse);
    sprintf(stry, "Координата y: %d ", y_mouse);
    txSetColor(TX_WHITE);
txDrawText(955,501,1158,556,strx);
txDrawText(958,585,1161,639,stry);
    }




    return stat;
}

HDC smena_classa(HDC pic, Objects* mesto)
{
    //Цикл?
    Win32::TransparentBlt (txDC(), 730 +   0, 450, 100, 130, plans[0].pic, 0, 0, 699, 895, TX_RED);
    Win32::TransparentBlt (txDC(), 730 + 120, 450, 100, 130, plans[1].pic, 0, 0, 628, 895, TX_RED);

    if (txMouseX() >= 730 && txMouseY() >= 450 &&
        txMouseX() <= 830 && txMouseY() <= 580 &&
        txMouseButtons()== 1)
    {
        pic = plans[0].pic;

        N_MEST = plans[0].N_MEST;
        for (int v = 0; v < plans[0].N_MEST; v = v + 1)
        {
            mesto[v] = plans[0].mesto[v];
        }
    }

    if (txMouseX() >= 850 && txMouseY() >= 450 &&
        txMouseX() <= 950 && txMouseY() <= 580 &&
        txMouseButtons()== 1)
    {
        pic = plans[1].pic;

        N_MEST = plans[1].N_MEST;
        for (int v = 0; v < plans[1].N_MEST; v = v + 1)
        {
            mesto[v] = plans[1].mesto[v];
        }
    }

    return pic;
}


