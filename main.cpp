#include "Lib/TXLib.h"

int main()
{
    txCreateWindow (1280, 895);

    txSetColor (TX_WHITE);
    txSetFillColor (TX_TRANSPARENT);
    txRectangle (50, 50, 300, 490);

    HDC  pic1 = txLoadImage ("Картинки/задний фон.bmp");
    txBitBlt (txDC(), 0, 0, 699,895, pic1, 0, 0);

    txRectangle (740, 190, 940, 320);
    HDC  pic2 = txLoadImage ("Картинки/ботан.bmp");
    txBitBlt (txDC(), 740, 190, 200,200, pic2, 0, 0);


    Win32::RoundRect (txDC(), 100, 200, 400, 500, 30, 30);

    return 0;
}
