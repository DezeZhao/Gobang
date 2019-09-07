#pragma once
#include "Chess.h"
class PE_Chesser
{
private:
    int color;

public:
    PE_Chesser(int color);
    Chess GiveNextChess(int x, int y);
};
