#pragma once
#define NOTSTART 0
#define DRAW 3
class Judge
{
private:
    int CurChesser; //0-black  1-white
public:
    Judge();
    int JudgeResult(const int ChessPad[15][15]);
    int JudgeNextChesser();
};

