#include "Lib/TXLib.h"
#include "windows.h"
#include "Picture.cpp"
#include "Stoly.cpp"

const char* active_category;
const char* menait;

bool GameOver = false;


HDC smena_classa(HDC pic, HDC pic1, HDC pic2)
{
    txRectangle (700, 1, 750, 50);

    txDrawText (700, 1, 750, 50, "1");


    txRectangle (750, 1, 800, 50);

    txDrawText (750, 1, 800, 50, "2");
    if(txMouseX() >= 750 &&
           txMouseY() >= 1 &&
           txMouseX() <= 800 &&
           txMouseY() <= 50 &&
           txMouseButtons()== 1)
    {
         pic = pic2;
    }

    return pic;
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




        txRectangle(1033,638,1242,687);    // âûõîä

        txDrawText (1040,653,1231,676, "Âûõîä");
        if(txMouseX() >= 1033 &&
               txMouseY() >= 638 &&
               txMouseX() <= 1242 &&
               txMouseY() <= 687 &&
               txMouseButtons()== 1)
        {
            txDisableAutoPause();
             GameOver = true;
        }
}
void menu ()
{
}    //ïîêà íå èñïîëüçóåòñÿ

void select_category()
{

            if (txMouseX() >= 1114 &&
               txMouseY() >= 180 &&
               txMouseX() <= 1269 &&
               txMouseY() <= 222 &&
               txMouseButtons()== 1)
            {
                active_category = "Ó÷èòåëÿ" ;
            }

            if (txMouseX() >= 736 &&
               txMouseY() >= 184 &&
               txMouseX() <= 885 &&
               txMouseY() <= 221 &&
               txMouseButtons()== 1)
            {
                active_category = "Ó÷åíèêè" ;
            }


            if (active_category == "Ó÷èòåëÿ")
                txSetFillColor(TX_BLUE);
            else
                txSetFillColor(TX_WHITE);
            txSetColor(TX_BLACK);
            Win32::RoundRect(txDC(), 1114, 180, 1269, 222, 50, 50);
            txDrawText(1114,180,1269,222,"Ó÷èòåëÿ");


            if (active_category == "Ó÷åíèêè")
                txSetFillColor(TX_BLUE);
            else
                txSetFillColor(TX_WHITE);
            txSetColor(TX_BLACK);
            Win32::RoundRect(txDC(), 728, 180, 883, 222, 50, 50);
           txDrawText(736,184,885,221,"Ó÷åíèêè");
}

void teleport_na_party(Picture* centr, Objects* mesto, int n_active)
{
    for (int nomer = 0; nomer < 8; nomer = nomer + 1)   // òåëåïîðò íà ïàðòó
        {


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


}

void teleport_na_stol_uchitela(Objects* stol_ychitela, Picture* centr, int n_active)
{
    if (txMouseX() >= stol_ychitela[0].x &&  // òåëåïîðò íà ñòîë ó÷èòåëÿ
       txMouseY() >= stol_ychitela[0].y &&
       txMouseX() <= stol_ychitela[0].x + 30  &&
       txMouseY() <= stol_ychitela[0].y + 30 &&
       txMouseButtons()== 1 && centr[n_active].visible)
    {
       centr[n_active].x  = stol_ychitela[0].x ;
       centr[n_active].y = stol_ychitela[0].y ;
    }
}
void draw_text()
{
    txDrawText(747,78,1242,100,"Èãðà íàõîäèòñÿ â ðàçðàáîòêå ");
    txDrawText(885,146,1195,179,"Âûáåðè ïåðñîíàæà");
}

void draw_fon(HDC pic1)
{
txBitBlt (txDC(), 0, 0, 699,895, pic1, 0, 0);
}

void okno_podskazki(int n_active, Picture* centr, Picture* variants)
{
    txDrawText(710, 480, 890, 640, "Âûáðàííûé ïåðñîíàæ");
        txRectangle(702, 550, 930, 800);
        if (n_active >= 0)
            Win32::TransparentBlt (txDC(), 702,  550, 228, 250, centr[n_active].pic, 0, 0, centr[n_active].width, variants[n_active].height, TX_WHITE);


}

void uroven_otstalosti(Picture* centr, int n_pics){

    txSetColor (TX_WHITE);
    int total = 0;
    for (int nomer = 0; nomer < n_pics; nomer = nomer + 1)
    {
        total = total + centr[nomer].otstalost;
    }

    char str[100];
    sprintf(str, "Óðîâåíü îòñòàëîñòè êëàññà %d / 100", total);
    txTextOut(965, 12, str);

}

int main()
{
    txTextCursor (false);
    bool developerMode = false;

    txCreateWindow (1280, 895);
    HDC  pic3 = txLoadImage ("Êàðòèíêè/çàäíèé ôîí 2.bmp");
    HDC  pic1 = txLoadImage ("Êàðòèíêè/çàäíèé ôîí.bmp");
    const int speed_x = 7;
    const int speed_y = 7;
    const int pic_width = 75;
    const int pic_height = 75;


    const int N_VARS = 6;
    Picture variants[N_VARS];
    variants[0] = {780, 240, 100, 100, txLoadImage("Êàðòèíêè/áîòàí.bmp"),false, "Ó÷åíèêè", 0};
    variants[1] = {920, 250, 100, 100, txLoadImage("Êàðòèíêè/ôàíåðà.bmp"),false, "Ó÷åíèêè", 10};
    variants[2] = {780, 410, 100, 100, txLoadImage("Êàðòèíêè/áðåâíî.bmp"),false, "Ó÷åíèêè", 11};
    variants[3] = {920, 410, 100, 100, txLoadImage("Êàðòèíêè/êàðòîøêà.bmp"),false, "Ó÷åíèêè", 28};
    variants[4] = {780, 240, 100, 100, txLoadImage("Êàðòèíêè/çëàÿ ó÷èëêà.bmp"),false,"Ó÷èòåëÿ", 0};
    variants[5] = {930, 230, 100, 100, txLoadImage("Êàðòèíêè/Ó÷èòåëü ïî òðóäó.bmp"),false,"Ó÷èòåëÿ", 0};

    Picture centr[1000];
    int n_pics = 0;
    int n_active = 0;


    mesto[0] = {247, 352};
    mesto[1] = {322, 344};
    mesto[2] = {383, 356};
    mesto[3] = {449, 356};
    mesto[4] = {246, 490};
    mesto[5] = {309, 488};
    mesto[6] = {385, 490};
    mesto[7] = {449, 491};


    stol_ychitela[0]  = {412, 115};



    while (GameOver == false)
    {
        txBegin();
        txSetFillColor(TX_BLACK);
        txClear();
        n_pics = del_all (n_pics);
        draw_fon(pic);

        txSetColor (TX_WHITE);
        txSetFillColor (TX_TRANSPARENT);


        pic = smena_classa(pic, pic1, pic3);
        exit();
        n_active = select_active(centr, n_pics,pic_width, pic_height, n_active);
        draw_variants(variants, N_VARS, active_category);

        okno_podskazki(n_active,centr, variants);
        developerMode = dev_mode(mesto, developerMode);
        select_category();
        teleport_na_party(centr, mesto, n_active);
        dvizhenie(centr, speed_x, speed_y, n_active);
        teleport_na_stol_uchitela(stol_ychitela, centr, n_active);
        draw_text();
        draw_centr_pic(centr, n_pics, pic_width, pic_height);
        n_pics = del_all (n_pics);
        uroven_otstalosti(centr, n_pics);


        n_pics = newCenterPic(variants, centr, N_VARS, n_pics, n_active) ;
        n_pics = deleteCenterPic(centr, n_pics, n_active);

        txEnd();
        txSleep(20);
    }

    del_pic(centr, n_pics, variants, N_VARS, pic1);
    return 0;

   }
