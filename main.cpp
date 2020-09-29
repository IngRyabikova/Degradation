#include "Lib/TXLib.h"
#include "windows.h"
int n_active ;
struct Picture
{
    int x;
    int y;
    int width;
    int height;
    HDC pic;
    bool visible;
};
struct Objects
{
    int x;
    int y;

};

bool GameOver = false;
/*bool click (int x1, int x2 , int y1, int y2)
{
   if ( txMouseX() >= x1 &&
               txMouseY() >= y1 &&
               txMouseX() <= x2 &&
               txMouseY() <= y2 &&
               txMouseButtons()== 1);
               {
               })
{
*/

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
}    //пока не используется



int main()
{
    txCreateWindow (1280, 895);

    HDC  pic1 = txLoadImage ("Картинки/задний фон.bmp");
    int speed_x = 5;
    int speed_y = 5;

    Picture variants[5];
    variants[0] = {740, 190, 200,157, txLoadImage("Картинки/ботан.bmp")};
    variants[1] = {990, 190, 267,287, txLoadImage("Картинки/фанера.bmp")};
    variants[2] = {740, 390, 234,234, txLoadImage("Картинки/бревно.bmp")};
    variants[3] = {990, 390, 252,189, txLoadImage("Картинки/картошка.bmp")};
    variants[4] = {740, 590, 248,248, txLoadImage("Картинки/злая училка.bmp")};

    Picture centr[5];
    centr[0] = {458, 608, 200,157, txLoadImage("Картинки/ботан.bmp"), false};
    centr[1] = {229, 379, 267,287, txLoadImage("Картинки/фанера.bmp"), false};
    centr[2] = {609, 479, 234,234, txLoadImage("Картинки/бревно.bmp"), false};
    centr[3] = {229, 379, 252,189, txLoadImage("Картинки/картошка.bmp"), false};
    centr[4] = {320, 787, 248,248, txLoadImage("Картинки/злая училка.bmp"), false};

    Objects mesto [8];
    mesto[0] = {247, 352};
    mesto[1] = {322, 344};
    mesto[2] = {383, 356};
    mesto[3] = {449, 356};
    mesto[4] = {246, 490};
    mesto[5] = {309, 488};
    mesto[6] = {385, 490};
    mesto[7] = {449, 491};

    /*Objects parta [5];
    parta[0] = {219, 330, 353,377};
    parta[1] = {218, 466, 352,515};
    parta[2] = {217, 467, 354,515};
    parta[4] = {357, 467, 491,515};
*/
    Objects stol_ychitela [0];
    stol_ychitela[0]  = {412, 115};



    while (GameOver == false)
    {

        txSetFillColor(TX_BLACK);
        txClear();
        txBegin();

        txSetColor (TX_WHITE);
        txSetFillColor (TX_TRANSPARENT);
        txRectangle (50, 50, 300, 490);



        txBitBlt (txDC(), 0, 0, 699,895, pic1, 0, 0);
        for (int nomer = 0; nomer < 5; nomer = nomer + 1)   // определение активного персонажа
         {

            if (txMouseX() >= centr[nomer].x &&
               txMouseY() >= centr[nomer].y &&
               txMouseX() <= centr[nomer].x + 100 &&
               txMouseY() <= centr[nomer].y + 100 &&
               txMouseButtons()== 1)
            {
                n_active = nomer;
            }
        }

        for (int nomer = 0; nomer < 8; nomer = nomer + 1)   // телепорт на парту
         {
        txRectangle (mesto[nomer].x, mesto[nomer].y, mesto[nomer].x + 30, mesto[nomer].y + 30);

            if (txMouseX() >= mesto[nomer].x &&
               txMouseY() >= mesto[nomer].y &&
               txMouseX() <= mesto[nomer].x + 30  &&
               txMouseY() <= mesto[nomer].y + 30 &&
               txMouseButtons()== 1 && centr[n_active].visible)
            {
               centr[n_active].x  = mesto[nomer].x ;
               centr[n_active].y = mesto[nomer].y ;
            }
        }


        txRectangle (stol_ychitela[0].x, stol_ychitela[0].y, stol_ychitela[0].x + 30, stol_ychitela[0].y + 30);

            if (txMouseX() >= stol_ychitela[0].x &&  // телепорт на стол учителя
               txMouseY() >= stol_ychitela[0].y &&
               txMouseX() <= stol_ychitela[0].x + 30  &&
               txMouseY() <= stol_ychitela[0].y + 30 &&
               txMouseButtons()== 1 && centr[n_active].visible)
            {
               centr[n_active].x  = stol_ychitela[0].x ;
               centr[n_active].y = stol_ychitela[0].y ;
            }


        if(GetAsyncKeyState(VK_LEFT) && centr[n_active].visible)
        {
            centr[n_active].x = centr[n_active].x  -speed_x;
        }

        if(GetAsyncKeyState(VK_RIGHT) && centr[n_active].visible)
        {
            centr[n_active].x = centr[n_active].x  +speed_x;
        }

        if(GetAsyncKeyState(VK_UP) && centr[n_active].visible )
        {
            centr[n_active].y = centr[n_active].y  -speed_y;
        }

        if(GetAsyncKeyState(VK_DOWN) && centr[n_active].visible  )
        {
            centr[n_active].y = centr[n_active].y  +speed_y;
        }

         for (int nomer = 0; nomer < 5; nomer = nomer + 1)
         {
            Win32::TransparentBlt (txDC(), variants[nomer].x,   variants[nomer].y, 100, 100, variants[nomer].pic, 0, 0, variants[nomer].width, variants[nomer].height, TX_WHITE);
         }


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


         for (int nomer = 0; nomer < 5; nomer = nomer + 1)
         {
            if (centr[nomer].visible)

                Win32::TransparentBlt (txDC(), centr[nomer].x,   centr[nomer].y, 100, 100, variants[nomer].pic, 0, 0, variants[nomer].width, centr[nomer].height, TX_WHITE);
         }


           txDrawText(747,78,1242,100,"Игра находится в разработке ");

           txDrawText(885,146,1195,179,"Выбери персонажа");







         // рисование ботана по клику (pic2)
         for (int nomer = 0; nomer < 5; nomer = nomer + 1)
         {

            if (txMouseX() >= variants[nomer].x &&
               txMouseY() >= variants[nomer].y &&
               txMouseX() <= variants[nomer].x + 100 &&
               txMouseY() <= variants[nomer].y + 100 &&
               txMouseButtons()== 1)
            {
                centr[nomer].visible = !centr[nomer].visible;
                txSleep(100);
            }
        }
        txSleep(20);
        exit();

    }

        for (int nomer = 0; nomer < 5; nomer = nomer + 1)
         {
        txDeleteDC(variants[nomer].pic);
         }

        for(int nomer = 0; nomer < 5; nomer = nomer + 1)
         {
        txDeleteDC(centr[nomer].pic);
         }

         txDeleteDC(pic1);
         txEnd();


    return 0;
}
