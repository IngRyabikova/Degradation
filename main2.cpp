


#include "TXLib.h"

int main()
    {
    txCreateWindow (1280,750);

    txSetColor (TX_WHITE);
    txSetFillColor (TX_TRANSPARENT);
    txRectangle (50, 50, 300, 490);

        txRectangle (4, 4, 1888, 77);
        HDC zadniy_fon = txLoadImage ("задний фон.bmp");
        txBitBlt (txDC(), 0, 0, 699, 895, zadniy_fon);
Win32::RoundRect (txDC(), 100, 200, 400, 500, 30, 30);



    return 0;
    }

