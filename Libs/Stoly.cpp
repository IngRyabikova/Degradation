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
{
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
    }

    return stat;
}

HDC smena_classa(HDC pic, Objects* mesto)
{     //    txRectangle(702, 550, 930, 800);
  Win32::TransparentBlt (txDC(), 734, 305, 100, 130, plans[0].pic, 0, 0, 699, 895, TX_RED);
  Win32::TransparentBlt (txDC(), 871, 305, 100, 130, plans[1].pic, 0, 0, 628, 895, TX_RED);
    txRectangle (784, 395, 837, 435);
    txRectangle (891, 387, 966, 404);

    if (txMouseX() >= 734 &&            txMouseY() >= 305+50 &&
        txMouseX() <= 833  &&       txMouseY() <= 433+50 &&
        txMouseButtons()== 1)
    {
        pic = plans[0].pic;

        N_MEST = plans[0].N_MEST;
        for (int v = 0; v < plans[0].N_MEST; v = v + 1)
        {
            mesto[v] = plans[0].mesto[v];
        }
    }

    if (txMouseX() >= 871 &&            txMouseY() >= 307+50 &&
        txMouseX() <= 969  &&       txMouseY() <= 401+50 &&
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


