#include "Lib/TXLib.h"
bool click (int x1, int x2)
{
    if (txMouseX
        () > x1 &&
        txMouseX()< x2)
{
return true;
}
else
    return false;
}


int main()
{

    bool GameOver = false;
    txCreateWindow (1280, 895);

    HDC  pic1 = txLoadImage ("Картинки/задний фон.bmp");
        HDC  pic2 = txLoadImage ("Картинки/ботан.bmp");

    while(GameOver == false)
    {
        txSetFillColor(TX_BLACK);
        txClear();

        txSetColor (TX_WHITE);
        txSetFillColor (TX_TRANSPARENT);
        txRectangle (50, 50, 300, 490);


        txBitBlt (txDC(), 0, 0, 699,895, pic1, 0, 0);

        txBitBlt (txDC(), 740, 190, 200,200, pic2, 0, 0);
        txRectangle(880,460,992,509);
          //txRectangle(880,460,992,509);

         if(txMouseX() >= 880 &&
               txMouseY() >= 460 &&
               txMouseX() <= 992 &&
               txMouseY() <= 509 &&
               txMouseButtons()== 1)
            {
                txDisableAutoPause();
                 GameOver = true;
            }

            if(txMouseX() >= 740 &&
               txMouseY() >= 190 &&
               txMouseX() <= 740 + 200 &&
               txMouseY() <= 190 + 200 &&
               txMouseButtons()== 1)
            {
                        txBitBlt (txDC(), 229, 379, 275,419, pic2, 0, 0);

            }

        if(GetAsyncKeyState(VK_MENU) &&  GetAsyncKeyState(VK_F4))
        {
                txDisableAutoPause();
                 GameOver = true;
        }
        if(GetAsyncKeyState(VK_ESCAPE))
        {
                txDisableAutoPause();
                 GameOver = true;
        }

           txDrawText(747,78,1242,100,"Игра находится в разработке ");

        Win32::RoundRect (txDC(), 100, 200, 400, 500, 30, 30);

        txSleep(20);

    }
    txDeleteDC(pic1);
  txDeleteDC(pic2);
    return 0;
}
