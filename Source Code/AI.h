#pragma once

struct Point
{
    int x;
    int y;
};
struct Situation
{
    int win5;
    int alive4;
    int rush4_1;
    int rush4_2;
    int alive3;
    int sleep3_2;
    int sleep3_1;
    int alive2;
    int sleep2_2;
    int sleep2_1;
    int nothreat;
};

class AI
{
private:
    static const int WIN5 = 0;
    static const int ALIVE4 = 1;
    static const int RUSH4_1 = 2;
    static const int RUSH4_2 = 3;
    static const int ALIVE3 = 4;
    static const int SLEEP3_2 = 5;
    static const int SLEEP3_1 = 6;
    static const int ALIVE2 = 7;
    static const int SLEEP2_2 = 8;
    static const int SLEEP2_1 = 9;
    static const int NOTHREAT = 10;

    static const int class1 = 100000;
    static const int class2 = 10000;
    static const int class3 = 5000;
    static const int class4 = 1000;
    static const int class5 = 500;
    static const int class6 = 400;
    static const int class7 = 100;
    static const int class8 = 90;
    static const int class9 = 50;
    static const int class10 = 10;
    static const int class11 = 9;
    static const int class12 = 5;
    static const int class13 = 2;
    static const int class14 = 1;
    static const int class15 = 0;

    static const int WHITE = 2;
    static const int BLACK = 1;
    static const int NO = 0;

public:
    int JudgeChessType(const int chess[9]);

    int Evaluate(const int state[15][15], Point point, int color);

    Point MaxScore(const int myscore[15][15], const int hisscore[15][15]);

    Point GetNextPoint(const int chesspad[15][15], int color);

    int Score(Situation status);

    void LinearAnalysis(int chess[9], const int state[15][15], Point point, int color, int direction);

    int GetLinearType(const int state[15][15], Point point, int color, int direction);
};
