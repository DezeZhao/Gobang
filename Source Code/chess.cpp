#include "Chess.h"
Chess::Chess(int color, int x, int y)
{
    this->color = color;
    this->x = x;
    this->y = y;
}

int Chess::GetColor()
{
    return color;
}

void Chess::GetPoint(int &x, int &y)
{
    x = this->x;
    y = this->y;
}

void Chess::SetColor(int color)
{
    this->color = color;
}

void Chess::SetPoint(int x, int y)
{
    this->x = x;
    this->y = y;
}
