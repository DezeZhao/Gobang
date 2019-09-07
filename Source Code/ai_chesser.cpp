#include "AI_Chesser.h"
AI_Chesser::AI_Chesser(int color)
{
    this->color = color;
}

Chess AI_Chesser::GiveNextChess(const int ChessPad[15][15], int &x, int &y)
{
    Point p;
    p = AI_player.GetNextPoint(ChessPad, color);
    x = p.x;
    y = p.y;
    return Chess(color, p.x, p.y);
}
