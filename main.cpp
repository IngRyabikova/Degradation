#include "Libs/TXLib.h"
#include "windows.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <cstring>
#include "Libs/Picture.cpp"
#include "Libs/Stoly.cpp"
#include "dirent.h"
bool GameOver = false;
using namespace std;

//Сюда могли бы прилететь планы, да и вообще это в отдельный файл просится


void exit ()
{
    txSetColor(TX_BLACK);
    txSetFillColor(TX_WHITE);
    drawkrugbutton(1046,745,1207,787, "Выход");

    if (GetAsyncKeyState(VK_MENU) && GetAsyncKeyState(VK_F4) ||
        GetAsyncKeyState(VK_ESCAPE))
    {
        txDisableAutoPause();
        GameOver = true;
    }


    if (txMouseX() >= 1046 && txMouseY() >= 745 &&
        txMouseX() <= 1207 && txMouseY() <= 787 &&
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
{   txSetColor (TX_WHITE);
    txDrawText(714,14,1239,68,"Цель - рассадить учеников так, чтобы\n класс получился mаксимально отсталым");
    txSetColor (TX_BLACK);
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
    txTextOut(850, 100, str);

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

int fillVariants(const char* address, Picture* variants, int N)
{
    setlocale(LC_ALL, "Russian");
    DIR *dir;
    struct dirent *ent;
    if ((dir = opendir (address)) !=NULL) {
        while((ent = readdir (dir)) !=NULL) {
            string str = ent->d_name;
            string folder = address;
            str = folder + "/" + str;

            if(str.find(".bmp") != -1)
            {
                variants[N] = {str.c_str(),false, "Ученики", 0};
                N = N + 1;
            }

        }
        closedir (dir);
    }

    return N;
}
int fillVariants2 (const char* address, Picture* variants, int N)
{
    setlocale(LC_ALL, "Russian");
    DIR *dir;
    struct dirent *ent;
    if ((dir = opendir (address)) !=NULL) {
        while((ent = readdir (dir)) !=NULL) {
            string str = ent->d_name;
            string folder = address;
            str = folder + "/" + str;

            if(str.find(".bmp") != -1)
            {
                //cout << str << endl;
                variants[N] = {str.c_str(),false, "Учителя", 0};
                N = N + 1;

            }

        }
        closedir (dir);
    }

    return N;
}
int main()
{
    char str[256];
    std::ofstream out("coord.txt"); // окрываем файл для записи
    ifstream fin("Settings.txt");

    txTextCursor (false);
    bool developerMode = false;

    txCreateWindow (1280, 895);
    txSetFillColor (TX_WHITE);

    //Планировки класса

    plans[0] = {699, 895, 700, 0, txLoadImage ("Картинки/Фоны/задний фон.bmp"), 8,
        {{247, 352},
         {322, 344},
         {383, 356},
         {449, 356},
         {246, 490},
         {309, 488},
         {385, 490},
         {449, 491},
        }
    };
    plans[1] = {625, 895, 750, 0, txLoadImage ("Картинки/Фоны/задний фон 2.bmp"), 7,
        {{100, 150},
         {100, 380},
         {100, 550},
         {280, 380},
         {280, 550},
         {480, 380},
         {480, 550},
        }
    };

    HDC pic = plans[0].pic;

    //Зачем нам скорость-то читать? Нам скорее расположение мест интереснее
    int speed_x;
    int speed_y;
    fin >> speed_x;
    fin >> speed_y;
    const int pic_width = 75;
    const int pic_height = 75;

    int N_VARS = 0;
    Picture variants[1000];

    //Хочу не заполнять категорию и координаты
    N_VARS = fillVariants("Картинки/Ученики/", variants, N_VARS);
    N_VARS = fillVariants2("Картинки/Учителя/", variants, N_VARS);

    //Координаты вариантов учеников и учителей
    int x_student = 730, y_student = 250;
    int x_teacher = 730, y_teacher = 250;
    for (int i = 0; i < N_VARS; i++)
    {
        if (variants[i].category == "Ученики")
        {
            variants[i].x = x_student;
            variants[i].y = y_student;

            x_student += 110;
            if (x_student > 1200)
            {
                 x_student = 730;
                 y_student += 110;
            }
        }

        else if (variants[i].category == "Учителя")
        {
            variants[i].x = x_teacher;
            variants[i].y = y_teacher;

            x_teacher += 110;
            if (x_teacher > 1200)
            {
                 x_teacher = 730;
                 y_teacher += 110;
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


    while (GameOver == false)
    {
        txBegin();
        txSetFillColor(TX_BLUE);
    if (GetAsyncKeyState(VK_MENU) && GetAsyncKeyState('S'))

    {
               if (out.is_open())
        {
            for (int nomer = 0; nomer < n_pics; nomer = nomer + 1)
    {

            //Добавляется новая центральная картинка
               out  << nomer << " " << centr[nomer].x << " " << centr[nomer].y << std::endl;


        }
         }
          txMessageBox ("Coxpaненo!");
          }

        txSetFillColor(TX_BLACK);
        txClear();
        n_pics = del_all (n_pics);
        draw_fon(pic);
        exit();

        txSetColor (TX_WHITE);
        txSetFillColor (TX_TRANSPARENT);
        pic = smena_classa(pic,mesto);

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

    del_pic(centr, n_pics, variants, N_VARS, pic);
    return 0;
}
