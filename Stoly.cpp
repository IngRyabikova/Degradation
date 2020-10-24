#include "Lib/TXLib.h"
struct Objects
{
    int x;
    int y;
};

int N_MEST = 8;
Objects mesto [8];
Objects stol_ychitela [1];


bool dev_mode(Objects* mesto, bool stat)
{
    if(GetAsyncKeyState(VK_TAB) &&  GetAsyncKeyState(VK_SPACE))
    {
        stat = !stat;
        txSleep(200);
    }

    if (stat == true)
    {
        for (int nomer = 0; nomer < 8; nomer = nomer + 1)   // телепорт на парту
        {
            txSetFillColor(TX_RED);
            txRectangle (mesto[nomer].x, mesto[nomer].y, mesto[nomer].x + 30, mesto[nomer].y + 30);
            txRectangle (stol_ychitela[0].x, stol_ychitela[0].y, stol_ychitela[0].x + 30, stol_ychitela[0].y + 30);
        }
    }

    return stat;
}
