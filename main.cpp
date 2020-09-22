#include "Lib/TXLib.h"
bool GameOver = false;
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
void exit ()
{

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
}
void menu ()
{
}



int main()
{


    bool drawObject1 = false;
    bool drawObject2 = false;
    bool drawObject3 = false;
    bool drawObject4 = false;

/* int drawObject[4];
    drawObject[0] = false;
   drawObject[1] = false;
    drawObject[2] = false;
    drawObject[3] = false;

  */
    txCreateWindow (1280, 895);

    HDC  pic1 = txLoadImage ("Картинки/задний фон.bmp");
    HDC  pic2 = txLoadImage ("Картинки/ботан.bmp");
    HDC  pic3 = txLoadImage ("Картинки/фанера.bmp");
    HDC  pic4 = txLoadImage ("Картинки/бревно.bmp");
    HDC  pic5 = txLoadImage ("Картинки/картошка.bmp");
    HDC  pic6 = txLoadImage ("Картинки/злая училка.bmp");

    while (GameOver == false)
    {
        txSetFillColor(TX_BLACK);
        txClear();

        txSetColor (TX_WHITE);
        txSetFillColor (TX_TRANSPARENT);
        txRectangle (50, 50, 300, 490);


        txBitBlt (txDC(), 0, 0, 699,895, pic1, 0, 0);

      // txRectangle (740, 190, 940, 320);
        txTransparentBlt (txDC(), 740, 190, 200, 157, pic2, 0, 0, TX_WHITE);

//txRectangle (990, 190, 1190, 320);
        txTransparentBlt (txDC(), 990, 190, 240,160, pic3, 0, 0, TX_WHITE);

       // txRectangle (740, 390, 940, 620);
        txTransparentBlt (txDC(), 740, 390, 200,200, pic4, 0, 0, TX_WHITE);

        //txRectangle (990, 590, 1190, 820);
        txTransparentBlt (txDC(), 990, 390, 180,160, pic5, 0, 0, TX_WHITE);

        //txRectangle(880,460,992,509);
        txTransparentBlt (txDC(), 740, 590, 200,240, pic6, 0, 0, TX_WHITE);



        txRectangle(933,638,1042,687);    // выход

          txDrawText(940,653,1031,676, "Выход");
         if(txMouseX() >= 933 &&
               txMouseY() >= 638 &&
               txMouseX() <= 1042 &&
               txMouseY() <= 687 &&
               txMouseButtons()== 1)
            {
                txDisableAutoPause();
                 GameOver = true;
            }
     // рисование ботана по клику (pic2)
        if(txMouseX() >= 740 &&
           txMouseY() >= 190 &&
           txMouseX() <= 740 + 200 &&
           txMouseY() <= 190 + 200 &&
           txMouseButtons()== 1)
        {
            drawObject1 = !drawObject1;
            txSleep(100);
        }
        // рисование бревна по клику (pic4)
            if(txMouseX() >= 740 &&
           txMouseY() >= 390 &&
           txMouseX() <= 940 &&
           txMouseY() <= 620 &&
           txMouseButtons()== 1)
        {
            drawObject2 = !drawObject2;
            txSleep(100);
        }


         // рисование картошки по клику   (pic5)
            if(txMouseX() >= 990 &&
           txMouseY() >= 390 &&
           txMouseX() <= 1180 &&
           txMouseY() <= 590 &&
           txMouseButtons()== 1)
        {
            drawObject3 = !drawObject3;
            txSleep(100);
        }


         // рисование фанеры по клику   (pic4)
            if(txMouseX() >= 990 &&
           txMouseY() >= 190 &&
           txMouseX() <= 240 &&
           txMouseY() <= 160 &&
           txMouseButtons()== 1)
        {
            drawObject4 = !drawObject4;
            txSleep(100);
        }

//990, 190, 240,160
if(drawObject1)
{
    txBitBlt (txDC(), 458, 608, 257,88, pic2, 0, 0);

}
if(drawObject2)
{
    txBitBlt (txDC(), 229, 379, 275,419, pic4, 0, 0);

}
if(drawObject3)
{
    txBitBlt (txDC(), 609, 479, 176,116, pic5, 0, 0);

}

if(drawObject4)
{
    txBitBlt (txDC(), 229, 379, 275,419, pic3, 0, 0);

}




    exit();

           txDrawText(747,78,1242,100,"Игра находится в разработке ");

           txDrawText(885,146,1195,179,"Выбери персонажа");


        txSleep(20);

    }
txDeleteDC(pic1);
txDeleteDC(pic2);
txDeleteDC(pic3);
txDeleteDC(pic4);
txDeleteDC(pic5);

    return 0;
}
