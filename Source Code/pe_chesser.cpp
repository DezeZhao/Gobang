#include "PE_Chesser.h"
PE_Chesser::PE_Chesser(int color)
{
    this->color = color;
}

Chess PE_Chesser::GiveNextChess(int x, int y)
{
    return Chess(color, x, y);
}
