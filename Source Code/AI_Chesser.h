#pragma once
#include "AI.h"
#include "Chess.h"
class AI_Chesser
{
private:
    int color;
    AI AI_player;
public:
    AI_Chesser(int color);
    Chess GiveNextChess(const int ChessPad[15][15], int &x, int &y);
};
