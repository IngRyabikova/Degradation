#include "Lib/TXLib.h"
#include "windows.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <cstring>
#include "Picture.cpp"
#include "Stoly.cpp"
bool GameOver = false;

struct Plan
{
    int x;
    int y;
    HDC pic;
    int N_MEST;
    Objects mesto[10];
};

Plan plans[2];



using namespace std;

//Сюда могли бы прилететь планы, да и вообще это в отдельный файл просится
HDC smena_classa(HDC pic, HDC pic1, HDC pic2, Objects* mesto)
{
    txRectangle (plans[0].x, 1, plans[0].x + 50, 50);
    txDrawText (plans[0].x, 1, plans[0].x + 50, 50, "1");
    txRectangle (plans[1].x, 1, plans[1].x + 50, 50);
    txDrawText (plans[1].x, 1, plans[1].x + 50, 50, "2");

    if (txMouseX() >= plans[0].x &&            txMouseY() >= 1 &&
        txMouseX() <= plans[0].x + 50 &&       txMouseY() <= 50 &&
        txMouseButtons()== 1)
    {
        pic = plans[0].pic;

        N_MEST = plans[0].N_MEST;
        for (int v = 0; v < plans[0].N_MEST; v = v + 1)
        {
            mesto[v] = plans[0].mesto[v];
        }
    }



    if (txMouseX() >= plans[1].x &&            txMouseY() >= 1 &&
        txMouseX() <= plans[1].x + 50 &&       txMouseY() <= 50 &&
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


void exit ()
{
    txSetColor(TX_BLACK);
    txSetFillColor(TX_WHITE);
    drawkrugbutton(1033,638,1242,687, "Выход");

    if (GetAsyncKeyState(VK_MENU) && GetAsyncKeyState(VK_F4) ||
        GetAsyncKeyState(VK_ESCAPE))
    {
        txDisableAutoPause();
        GameOver = true;
    }


    if (txMouseX() >= 1033 && txMouseY() >= 638 &&
        txMouseX() <= 1242 && txMouseY() <= 687 &&
        txMouseButtons()== 1)
    {
        txDisableAutoPause();
        GameOver = true;
    }
}

void select_category()
{
    if (txMouseX() >= 1114 &&       txMouseY() >= 180 &&
       txMouseX() <= 1269 &&       txMouseY() <= 222 &&       txMouseButtons()== 1)
    {
        active_category = "Учителя" ;
    }

    if (txMouseX() >= 736 &&       txMouseY() >= 184 &&
       txMouseX() <= 885 &&       txMouseY() <= 221 &&       txMouseButtons()== 1)
    {
        active_category = "Ученики" ;
    }


    txSetColor(TX_BLACK);
    txSetFillColor(TX_WHITE);
    if (active_category == "Учителя")
        txSetFillColor(TX_BLUE);

    drawkrugbutton(1114, 180,"Учителя");


    txSetFillColor(TX_WHITE);
    if (active_category == "Ученики")
        txSetFillColor(TX_BLUE);
    drawkrugbutton(728, 180,"Ученики");
}

void teleport_na_party(Picture* centr, Objects* mesto, int n_active, int N_MEST)
{
    for (int nomer = 0; nomer < N_MEST; nomer = nomer + 1)   // телепорт на парту
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
    if (txMouseX() >= stol_ychitela[0].x &&  // телепорт на стол учителя
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
    txDrawText(747,78,1242,100,"Игра находится в разработке ");
}

void draw_fon(HDC pic1)
{
    txBitBlt (txDC(), 0, 0, 699,895, pic1, 0, 0);
}

void okno_podskazki(int n_active, Picture* centr, Picture* variants , int n_pics)
{
    txDrawText(710, 480, 890, 640, "Выбранный персонаж");
    txRectangle(702, 550, 930, 800);
    if (n_active >= 0 && n_pics > 0)
        Win32::TransparentBlt (txDC(), 702,  550, 228, 250, centr[n_active].pic, 0, 0, centr[n_active].width, variants[n_active].height, TX_WHITE);
    else
        n_active = 0;
}

void uroven_otstalosti(Picture* centr, int n_pics){

    txSetColor (TX_WHITE);
    int total = 0;
    for (int nomer = 0; nomer < n_pics; nomer = nomer + 1)
    {
        total = total + centr[nomer].otstalost;
    }

    char str[100];
    sprintf(str, "Уровень отсталости класса %d / 100", total);
    txTextOut(965, 12, str);

}

void opredelenie_razmera(Picture* variants, int N)
{
    for (int nomer = 0; nomer < N; nomer++)
    {
        BITMAPFILEHEADER bmfHeader;
        BITMAPINFOHEADER bmiHeader;
        FILE* pFile = fopen (variants[nomer].adres , "rb" );
        fread( (LPSTR)&bmfHeader, 1, sizeof(bmfHeader), pFile );
        fread( (LPSTR)&bmiHeader, 1, sizeof(bmiHeader), pFile );

        variants[nomer].width = bmiHeader.biWidth ;
        variants[nomer].height = bmiHeader.biHeight ;
        variants[nomer].pic = txLoadImage(variants[nomer].adres);
    }
}

int main()
{
    char str[256];
    //cin.getline(str, 256, ';'));
    //cout << str;

    ifstream fin("Settings.txt");

    txTextCursor (false);
    bool developerMode = false;

    txCreateWindow (1280, 895);


    plans[0] = {700, 0, txLoadImage ("Картинки/задний фон.bmp"), 3,
        {{247, 352},
         {322, 344},
         {383, 356}
        }
    };
    plans[1] = {750, 0, txLoadImage ("Картинки/задний фон 2.bmp"), 2,
        {{100, 150},
         {100, 380}
        }
    };




     /* Ты на фига места-то стер? Они же тоже в plans[0] входят
     N_MEST = 8;	        N_MEST = plans[0].N_MEST;
        mesto[0] = {247, 352};	        for (int v = 0; v < plans[0].N_MEST; v = v + 1)
        mesto[1] = {322, 344};	        {
        mesto[2] = {383, 356};	            mesto[v] = plans[0].mesto[v];
        mesto[3] = {449, 356};	        }
        mesto[4] = {246, 490};
        mesto[5] = {309, 488};
        mesto[6] = {385, 490};
        mesto[7] = {449, 491};



        N_MEST = 7;	        N_MEST = plans[1].N_MEST;
        mesto[0] = {100, 150};          for (int v = 0; v < plans[1].N_MEST; v = v + 1)
        mesto[1] = {100, 380};	        {
        mesto[2] = {100, 550};	            mesto[v] = plans[1].mesto[v];
        mesto[3] = {280, 380};	        }
        mesto[4] = {280, 550};
        mesto[5] = {480, 380};
        mesto[6] = {480, 550};
     */
    HDC  pic3 = txLoadImage ("Картинки/задний фон 2.bmp");
    HDC  pic1 = txLoadImage ("Картинки/задний фон.bmp");
    HDC pic = pic1;

    //Зачем нам скорость-то читать? Нам скорее расположение мест интереснее
    int speed_x;
    int speed_y;
    fin >> speed_x;
    fin >> speed_y;
    const int pic_width = 75;
    const int pic_height = 75;

    const int N_VARS = 6;
    Picture variants[N_VARS];
    //Хочу не заполнять категорию и координаты
    variants[0] = {0, 240, "Картинки/Ученики/ботан.bmp",false, "Ученики", 0};
    variants[1] = {0, 240, "Картинки/фанера.bmp",false, "Ученики", 10};
    variants[2] = {0, 410, "Картинки/Ученики/бревно.bmp",false, "Ученики", 11};
    variants[3] = {0, 410, "Картинки/картошка.bmp",false, "Ученики", 28};
    variants[4] = {0, 240, "Картинки/злая училка.bmp",false,"Учителя", 0};
    variants[5] = {0, 240, "Картинки/Учитель по труду.bmp",false,"Учителя", 0};



    int x_student = 780, y_student = 350;
    int x_teacher = 780, y_teacher = 350;

//Координаты вариантов людей
    for (int i = 0; i < N_VARS; i++)
    {
        if (variants[i].category == "Ученики")
        {
            variants[i].x = x_student;
            variants[i].y = y_student;
            x_student += 110;

            if (x_student > 1200)
            {
                 x_student = 780; //y = 150;
                 y_student += 140;
            }
        }

        else if (variants[i].category == "Учителя")
        {
            variants[i].x = x_teacher;
            variants[i].y = y_teacher;
            x_teacher += 110;

            if (x_teacher > 1200)
            {
                 x_teacher = 780; //y = 150;
                 y_teacher += 140;
            }
        }
    }


    opredelenie_razmera(variants, N_VARS);



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


    //Тут редактирование
    while (GameOver == false)
    {
        txBegin();
        txSetFillColor(TX_BLACK);
        txClear();
        n_pics = del_all (n_pics);
        draw_fon(pic);
        exit();

        txSetColor (TX_WHITE);
        txSetFillColor (TX_TRANSPARENT);
        pic = smena_classa(pic, pic1, pic3, mesto);

        txSelectFont("Arial", 30);
        txSetColor(TX_WHITE, 5);
        txSetFillColor(TX_BLACK);
        txDrawText(885,146,1195,179,"Выбери персонажа");


        n_active = select_active(centr, n_pics,pic_width, pic_height, n_active);
        draw_variants(variants, N_VARS, active_category);

        okno_podskazki(n_active,centr, variants, n_pics);
        developerMode = dev_mode(mesto, developerMode);
        select_category();
        teleport_na_party(centr, mesto, n_active, N_MEST);
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
