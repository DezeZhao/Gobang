#include "ChessBoard.h"
ChessBoard::ChessBoard()
{
    LastX = 0;
    LastY = 0;
    for (int i = 0; i < 15; i++)
        for (int j = 0; j < 15; j++)
            ChessPadStatus[i][j] = 0;
}
void ChessBoard::AddChess(Chess chess)
{
    if (ChessPadStatus[LastX][LastY])
        ChessPadStatus[LastX][LastY] -= 2;

    chess.GetPoint(LastX, LastY); //LastX=chess.x;LastY=chess.y;

    if (chess.GetColor()) //  color=chess.color=this.color;  color=1-white  color=0-black
        ChessPadStatus[LastX][LastY] = 4;
    else
        ChessPadStatus[LastX][LastY] = 3;
}

void ChessBoard::GetChessStatus(int ChessPadStatus[15][15])
{
    for (int i = 0; i < 15; i++)
        for (int j = 0; j < 15; j++)
            ChessPadStatus[i][j] = this->ChessPadStatus[i][j];
}
