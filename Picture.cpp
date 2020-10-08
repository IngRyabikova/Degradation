#include "Lib/TXLib.h"

struct Picture
{
    int x;
    int y;
    int width;
    int height;
    HDC pic;
    bool visible;
    const char* category;
};

void draw_variants(Picture* variants, int N_VARS, const char* active_category)
{
    for (int nomer = 0; nomer < N_VARS; nomer = nomer + 1)
    {
        if (variants[nomer].category == active_category){
            Win32::TransparentBlt (txDC(), variants[nomer].x,   variants[nomer].y, 100, 100, variants[nomer].pic, 0, 0, variants[nomer].width, variants[nomer].height, TX_WHITE);
        }
    }
}
