///\file main.cpp
#include "Libs/TXLib.h"
#include "windows.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <cstring>
#include "Libs/Picture.cpp"
#include "Libs/Teleport.cpp"
#include "Libs/Stoly.cpp"

bool GameOver = false;
using namespace std;
/// �����
void exit ()
{
    txSetColor(TX_BLACK);
    txSetFillColor(TX_WHITE);
    drawkrugbutton(1046,745,1207,787, "�����");

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
///  ����� ���������(������� ��� �������)
void select_category()
{
    if (txMouseX() >= 1114 &&       txMouseY() >= 180 &&
       txMouseX() <= 1269 &&       txMouseY() <= 222 &&       txMouseButtons()== 1)
    {
        active_category = "�������" ;
    }

    if (txMouseX() >= 736 &&       txMouseY() >= 184 &&
       txMouseX() <= 885 &&       txMouseY() <= 221 &&       txMouseButtons()== 1)
    {
        active_category = "�������" ;
    }


    txSetColor(TX_BLACK);
    txSetFillColor(TX_WHITE);
    if (active_category == "�������")
        txSetFillColor(TX_BLUE);

    drawkrugbutton(1114, 180,"�������");


    txSetFillColor(TX_WHITE);
    if (active_category == "�������")
        txSetFillColor(TX_BLUE);
    drawkrugbutton(728, 180,"�������");
}
/// ��������� ������
void draw_text()
{   txSetColor (TX_WHITE);
    txDrawText(714,14,1239,68,"���� - ��������� �������� ���, �����\n ����� ��������� ����������� ��������");
    txSetColor (TX_BLACK);
    txDrawText(747,78,1242,100,"���� ��������� � ���������� ");
}
/// ��������� ����
void draw_fon(HDC pic1)
{
    txBitBlt (txDC(), 0, 0, 699,895, pic1, 0, 0);
}
 /// ����������� ���������� ��������� � ��������
void okno_podskazki(int n_active, Picture* centr, Picture* variants , int n_pics)
{
    txRectangle(700, 700, 850, 850);
    if (n_active >= 0 && n_pics > 0)
        Win32::TransparentBlt (txDC(), 700, 700, 150, 150, centr[n_active].pic, 0, 0, centr[n_active].width, variants[n_active].height, TX_WHITE);
    else
        n_active = 0;

    txDrawText(675, 675, 965, 695, "��������� ��������");
}
/// ������� � ����� ������ ���������� ����� ������
int uroven_otstalosti(Picture* centr, int n_pics){

    txSetColor (TX_WHITE);
    int total = 0;
    for (int nomer = 0; nomer < n_pics; nomer++)
        if (centr[nomer].x != centr[nomer-1].x ||
            centr[nomer].y != centr[nomer-1].y)
        total = total + centr[nomer].otstalost;

    char str[100];
    sprintf(str, "������� ���������� ������ %d / 100", total);
    txTextOut(850, 100, str);
    return total;
}
/// �������������� ����������� ������� ��������
void opredelenie_razmera(Picture* variants, int N)
{
    for (int nomer = 0; nomer < N; nomer++)
    {
        BITMAPFILEHEADER bmfHeader;
        BITMAPINFOHEADER bmiHeader;
        FILE* pFile = fopen (variants[nomer].adres.c_str() , "rb" );
        fread( (LPSTR)&bmfHeader, 1, sizeof(bmfHeader), pFile );
        fread( (LPSTR)&bmiHeader, 1, sizeof(bmiHeader), pFile );

        variants[nomer].width = bmiHeader.biWidth ;
        variants[nomer].height = bmiHeader.biHeight ;
        variants[nomer].pic = txLoadImage(variants[nomer].adres.c_str());
    }
}



/// ���������� �� ������ ���������� ���� ������� (Open).
void open_file()
{

    if (GetAsyncKeyState('A')){

 OPENFILENAME ofn;       // ��������� �����. ����� �������
char szFile[260];       // ����� ��� ����� �����
HWND hwnd;              // ����-��������
HANDLE hf;              // ���������� �����

// ������������� ��������� OPENFILENAME
ZeroMemory(&ofn, sizeof(ofn));
ofn.lStructSize = sizeof(ofn);
ofn.hwndOwner = txWindow();
ofn.lpstrFile = szFile;
ofn.nMaxFile = sizeof(szFile);
ofn.lpstrFilter = ".txt";
ofn.nFilterIndex = 1;
ofn.lpstrFileTitle = NULL;
ofn.nMaxFileTitle = 0;
ofn.lpstrInitialDir = NULL;
ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;



if (GetOpenFileName(&ofn)==TRUE)
{
  ifstream file(ofn.lpstrFile);
  while (file.good())
                {
                    string strokaX;
                    getline(file, strokaX);
                   /* Bed2[n_pics].x = atoi(strokaX.c_str());

                    getline(file, strokaY);
                    Bed2[n_pics].y = atoi(strokaY.c_str());

                    getline(file, address);
                    Bed2[n_pics].address = address.c_str();
                    Bed2[n_pics].visible = true;
                    Bed2[n_pics].picture = txLoadImage(Bed2[n_pics].address.c_str());

                    Bed2[n_pics].width = getWidth (Bed2[n_pics].address.c_str());
                    Bed2[n_pics].height = getHeight(Bed2[n_pics].address.c_str());*/
//                    n_pics = n_pics + 1;
                }
                txMessageBox("Caa?ocea...");

}

  }
   }


///���������� ��������� �������� � ��������
void koordvarints(Picture* variants, int N_VARS)
{
    int x_student = 730, y_student = 250;
    int x_teacher = 730, y_teacher = 250;
    for (int i = 0; i < N_VARS; i++)
    {
        if (variants[i].category == "�������")
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

        else if (variants[i].category == "�������")
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
}
int main()
{
     /// ��������� ���� ��� ������
    std::ofstream out("coord.txt");
    ifstream fin("Settings.txt");

    txTextCursor (false);
    bool developerMode = false;

    txCreateWindow (1280, 895);
    txSetFillColor (TX_WHITE);

    ///������(����)
    plans[0] = {699, 895, 700, 0, txLoadImage ("��������/����/������ ���.bmp"), 29,
        {{230, 355},         {295, 355},         {360, 355},         {425, 355},
         {230, 490},         {295, 490},         {360, 490},         {425, 490},
         {230, 625},         {295, 625},         {360, 625},         {425, 625},
         {230, 735},         {295, 735},         {360, 735},         {425, 735},
         {77, 106},          {77, 216},          {77, 334},          {77, 463},          {77, 586},         {77, 706},
         {560, 170},         {560, 298},         {560, 423},         {560, 546},         {560, 675},
         {265, 53},
         {331, 91},
        }
    };
    plans[2] = {625, 895, 750, 0, txLoadImage ("��������/����/������ ��� 2.bmp"), 7,
        {{100, 150},
         {100, 380},
         {100, 550},
         {280, 380},
         {280, 550},
         {480, 380},
         {480, 550},
        }
    };

    plans[1] = {630, 882, 800, 0, txLoadImage ("��������/����/������ ��� 3.bmp"), 28,
        {{50, 235},
         {114, 235},
         {256, 235},
         {315, 235},
         {443, 235},
         {502, 235},

         {50, 360},
         {114, 360},
         {256, 360},
         {315, 360},
         {443, 360},
         {502, 360},

         {50, 485},
         {114, 485},
         {256, 485},
         {315, 485},
         {443, 485},
         {502, 485},


         {50, 610},
         {114, 610},
         {256, 610},
         {315, 610},
         {443, 610},
         {502, 610},

         {50, 737},
         {114, 737},
         {443, 737},
         {502, 737},
        }
    };

    HDC pic = plans[0].pic;



    /// �������� ��������� �� ��� �
    int speed_x;
    /// �������� ��������� �� ��� �
    int speed_y;
    /// ������ �������� ��������� �� ��� � �� ����� Settings.txt
    fin >> speed_x;
    /// ������ �������� ��������� �� ��� � �� ����� Settings.txt
    fin >> speed_y;
    /// ������ ���� �������� (����� �����)
    const int pic_width = 75;
    /// ������ ���� �������� (����� �����)
    const int pic_height = 75;

    int N_VARS = 0;
    Picture variants[1000];

    pic = plans[0].pic;
    N_MEST = plans[0].N_MEST;
    for (int v = 0; v < plans[0].N_MEST; v++)
    {
        mesto[v] = plans[0].mesto[v];
    }

    N_VARS = fillVariants("��������/�������/", variants, N_VARS, "�������");
    N_VARS = fillVariants("��������/�������/", variants, N_VARS, "�������");

    opredelenie_razmera(variants, N_VARS);

    Picture centr[1000];
    int n_pics = 0;
    int n_active = 0;

    ///��������� ���������� ������
    int total = 0;

    /// ���� �� �������� �����(���������� GameOver ������ ����� true)
    while (GameOver == false)
    {
        txBegin();
        txSetFillColor(TX_BLUE);

    //��������
    if(GetAsyncKeyState(VK_SNAPSHOT))
    {
      ScreenCapture(0, 0, 699,895, "screen.bmp", txWindow());
      txMessageBox ("�������� �������.");
    }

    if (GetAsyncKeyState(VK_MENU) && GetAsyncKeyState('S'))

    {
               if (out.is_open())
        {
            for (int nomer = 0; nomer < n_pics; nomer++)
    {


               out  << n_pics << " " <<  centr[nomer].adres << " " << centr[nomer].x << " " << centr[nomer].y << std::endl;


        }
         }
          txMessageBox ("Coxpa���o!");
          }

        txSetFillColor(TX_BLACK);
        txClear();
        n_pics = del_all (n_pics);
        draw_fon(pic);
        exit();
        koordvarints(variants,N_VARS);
        txSetColor (TX_WHITE);
        txSetFillColor (TX_TRANSPARENT);
        pic = smena_classa(pic,mesto, &n_pics, total);

        txSelectFont("Arial", 30);
        txSetColor(TX_WHITE, 5);
        txSetFillColor(TX_BLACK);
        txDrawText(885,146,1195,179,"������ ���������");
        open_file();

        n_active = select_active(centr, n_pics,pic_width, pic_height, n_active);
        draw_variants(variants, N_VARS, active_category);

        okno_podskazki(n_active,centr, variants, n_pics);
        developerMode = dev_mode(mesto, developerMode);
        select_category();
        teleport_na_party(centr, mesto, n_active, N_MEST);
        dvizhenie(centr, speed_x, speed_y, n_active);
        draw_text();
        draw_centr_pic(centr, n_pics, pic_width, pic_height);
        n_pics = del_all (n_pics);
        total = uroven_otstalosti(centr, n_pics);


        n_pics = newCenterPic(variants, centr, N_VARS, n_pics, N_MEST) ;
        n_pics = deleteCenterPic(centr, n_pics, n_active);
        txEnd();
        txSleep(20);
    }



    del_pic(centr, n_pics, variants, N_VARS, plans);
    return 0;
}
