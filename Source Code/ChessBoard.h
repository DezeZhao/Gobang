#pragma once
#include "Chess.h"
class ChessBoard
{
private:
    int LastX;
    int LastY;
    int ChessPadStatus[15][15];

public:
    ChessBoard();
    void AddChess(Chess chess);
    void GetChessStatus(int ChessPadStatus[15][15]);
};

