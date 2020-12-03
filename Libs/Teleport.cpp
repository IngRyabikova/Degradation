///\file Teleport.cpp
#include "TXLib.h"
#include "Picture.cpp"
#include "Stoly.cpp"
/// ����������� ���������� ��������� �� �����
void teleport_na_party(Picture* centr, Objects* mesto, int n_active, int N_MEST)
{
    for (int nomer = 0; nomer < N_MEST; nomer++)
    {
        if (txMouseX() >= mesto[nomer].x &&
           txMouseY() >= mesto[nomer].y &&
           txMouseX() <= mesto[nomer].x + PLACE_SIZE  &&
           txMouseY() <= mesto[nomer].y + PLACE_SIZE &&
           txMouseButtons()== 1 && centr[n_active].visible)
        {
           centr[n_active].x  = mesto[nomer].x ;
           centr[n_active].y = mesto[nomer].y ;
        }
    }
}

