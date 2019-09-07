#include "AI.h"
#include <iostream>
#include <vector>
using namespace std;
Point AI::GetNextPoint(const int chesspad[15][15], int color)
{
    int me = color + 1;
    int rival;

    int MyScore[15][15] = {{0}};
    int RivalScore[15][15] = {{0}};
    int temp[15][15] = {{0}};
    int flag = 0;
    int k = 0, h = 0;
    for (k = 0; k < 15; k++) {
        for (h = 0; h < 15; h++) {
            if (chesspad[k][h] > 0) {
                flag = 1;
                break;
            }
        }
        if (flag)
            break;
    }
    if (k == 15 && h == 15) {
        Point point = {7, 7};
        return point;
    }

    for (int i = 0; i < 15; i++) {
        for (int j = 0; j < 15; j++) {
            if (chesspad[i][j] > 2)
                temp[i][j] = chesspad[i][j] - 2;
            else
                temp[i][j] = chesspad[i][j];
        }
    }

    for (int i = 0; i < 15; i++)
        for (int j = 0; j < 15; j++) {
            Point point;
            int score;

            point.x = i;
            point.y = j;

            score = Evaluate(temp, point, me);
            MyScore[i][j] = score;

            if (me == BLACK)
                rival = WHITE;
            else
                rival = BLACK;

            score = Evaluate(temp, point, rival);
            RivalScore[i][j] = score;
        }

    return MaxScore(MyScore, RivalScore);
}

int AI::Evaluate(const int state[15][15], Point point, int color)
{
    Situation status = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    if (state[point.x][point.y])
        return class15;

    for (int direction = 0; direction < 4; direction++) {
        int type;
        type = GetLinearType(state, point, color, direction);

        switch (type) {
        case WIN5:
            status.win5++;
            break;
        case ALIVE4:
            status.alive4++;
            break;
        case RUSH4_1:
            status.rush4_1++;
            break;
        case RUSH4_2:
            status.rush4_2++;
            break;
        case ALIVE3:
            status.alive3++;
            break;
        case SLEEP3_2:
            status.sleep3_2++;
            break;
        case SLEEP3_1:
            status.sleep3_1++;
            break;
        case ALIVE2:
            status.alive2++;
            break;
        case SLEEP2_2:
            status.sleep2_2++;
            break;
        case SLEEP2_1:
            status.sleep2_1++;
            break;
        case NOTHREAT:
            status.nothreat++;
            break;
        default:
            break;
        }
    }
    return Score(status);
}

int AI::Score(Situation status)
{
    int rush4_1 = status.rush4_1 + status.rush4_2;
    int alive3 = status.alive3 + status.sleep3_2;
    int alive2 = status.alive2 + status.sleep2_2;

    if (status.win5 >= 1)
        return class1;

    if (status.alive4 >= 1 || rush4_1 >= 2 || (rush4_1 >= 1 && alive3 >= 1))
        return class2;

    if (alive3 >= 2)
        return class3;

    if (status.sleep3_1 >= 1 && status.alive3 >= 1)
        return class4;

    if (status.rush4_1 >= 1)
        return class5;

    if (status.rush4_2 >= 1)
        return class6;

    if (status.alive3 >= 1)
        return class7;

    if (status.sleep3_2 >= 1)
        return class8;

    if (status.alive2 >= 2)
        return class9;

    if (status.alive2 >= 1)
        return class10;

    if (status.sleep2_2 >= 1)
        return class11;

    if (status.sleep3_1 >= 1)
        return class12;

    if (status.sleep2_1 >= 1)
        return class13;

    return class14;
}

int AI::GetLinearType(const int state[15][15], Point point, int color, int direction)
{
    int type;
    int chess[9] = {0};
    LinearAnalysis(chess, state, point, color, direction);
    type = JudgeChessType(chess);
    return type;
}

void AI::LinearAnalysis(int chess[9], const int state[15][15], Point point, int color, int direction)
{
    int rival;
    if (color == BLACK)
        rival = WHITE;
    else
        rival = BLACK;
    chess[4] = color;
    switch (direction) {
    case 0: //??

        for (int i = point.x, j = 1; j <= 4; j++) {
            int column = point.y - j;
            if (column < 0) {
                for (; j <= 4; j++)
                    chess[4 - j] = rival;
                break;
            }
            chess[4 - j] = state[i][column];
        }
        for (int i = point.x, j = 1; j <= 4; j++) {
            int column = point.y + j;
            if (column > 14) {
                for (; j <= 4; j++)
                    chess[4 + j] = rival;
                break;
            }
            chess[4 + j] = state[i][column];
        }
        break;
    case 1:
        for (int j = point.y, i = 1; i <= 4; i++) {
            int row = point.x - i;
            if (row < 0) {
                for (; i <= 4; i++)
                    chess[4 - i] = rival;
                break;
            }
            chess[4 - i] = state[row][j];
        }
        for (int i = 1, j = point.y; i <= 4; i++) {
            int row = point.x + i;
            if (row > 14) {
                for (; i <= 4; i++)
                    chess[4 + i] = rival;
                break;
            }
            chess[4 + i] = state[row][j];
        }
        break;
    case 2:
        for (int i = 1, j = 1; i <= 4; i++, j++) {
            int row = point.x - i;
            int column = point.y - j;
            if (row < 0 || column < 0) {
                for (; i <= 4; i++)
                    chess[4 - i] = rival;
                break;
            }
            chess[4 - i] = state[row][column];
        }
        for (int i = 1, j = 1; i <= 4; i++, j++) {
            int row = point.x + i;
            int column = point.y + j;
            if (row > 14 || column > 14) {
                for (; i <= 4; i++)
                    chess[4 + i] = rival;
                break;
            }
            chess[4 + i] = state[row][column];
        }
        break;
    case 3:
        for (int i = 1, j = 1; i <= 4; i++, j++) {
            int row = point.x + i;
            int column = point.y - j;
            if (row > 14 || column < 0) {
                for (; i <= 4; i++)
                    chess[4 - i] = rival;
                break;
            }
            chess[4 - i] = state[row][column];
        }
        for (int i = 1, j = 1; i <= 4; i++, j++) {
            int row = point.x - i;
            int column = point.y + j;
            if (row < 0 || column > 14) {
                for (; i <= 4; i++)
                    chess[4 + i] = rival;
                break;
            }
            chess[4 + i] = state[row][column];
        }
        break;
    default:
        break;
    }
}

int AI::JudgeChessType(const int chess[9])
{
    int left = 0, right = 0;
    int Lc = 0, Rc = 0;
    int count = 1;
    int me = chess[4];
    int rival;
    rival = (me == BLACK) ? WHITE : BLACK;

    for (int i = 1; i <= 4; i++) {
        if (chess[4 - i] == me)
            count++;
        else {
            left = 4 - i;
            Lc = chess[4 - i];
            break;
        }
    }
    for (int i = 1; i <= 4; i++) {
        if (chess[4 + i] == me)
            count++;
        else {
            right = 4 + i;
            Rc = chess[4 + i];
            break;
        }
    }

    if (count >= 5)
        return WIN5;
    if (count == 4) {
        if (Lc == NO && Rc == NO)
            return ALIVE4;
        else if (Lc == rival && Rc == rival)
            return NOTHREAT;
        else if (Lc == NO || Rc == NO)
            return RUSH4_1;
    }
    if (count == 3) { //???3?
        int Lc1 = chess[left - 1];
        int Rc1 = chess[right + 1];

        if (Lc == NO && Rc == NO) {
            if (Lc1 == rival && Rc1 == rival)
                return SLEEP3_1;
            else if (Lc1 == me || Rc1 == me)
                return RUSH4_2;
            else if (Lc1 == NO || Rc1 == NO)
                return ALIVE3;

        } else if (Lc == rival && Rc == rival) {
            return NOTHREAT;
        } else if (Lc == NO || Rc == NO) {
            if (Lc == rival) {
                if (Rc1 == rival)
                    return NOTHREAT;
                if (Rc1 == NO)
                    return SLEEP3_1;
                if (Rc1 == me)
                    return RUSH4_2;
            }
            if (Rc == rival) {
                if (Lc1 == rival)
                    return NOTHREAT;
                if (Lc1 == NO)
                    return SLEEP3_1;
                if (Lc1 == me)
                    return RUSH4_2;
            }
        }
    }
    if (count == 2) { //???2?
        int Lc1 = chess[left - 1];
        int Rc1 = chess[right + 1];
        int Lc2 = chess[left - 2];
        int Rc2 = chess[right + 2];

        if (Lc == NO && Rc == NO) //????????
        {
            if ((Rc1 == NO && Rc2 == me) || (Lc1 == NO && Lc2 == me))
                return SLEEP3_1; //?3
            else if (Lc1 == NO && Rc1 == NO)
                return ALIVE2; //?2
            if ((Rc1 == me && Rc2 == rival) || (Lc1 == me && Lc2 == rival))
                return SLEEP3_1; //?3
            if ((Rc1 == me && Rc2 == me) || (Lc1 == me && Lc2 == me))
                return RUSH4_2; //?4
            if ((Rc1 == me && Rc2 == NO) || (Lc1 == me && Lc2 == NO))
                return SLEEP3_2; //??->??3
            //?????????NOTHREAT
        } else if (Lc == rival && Rc == rival) //?????????
            return NOTHREAT;
        else if (Lc == NO || Rc == NO) //???????????
        {
            if (Lc == rival) {
                if (Rc1 == rival || Rc2 == rival) {
                    return NOTHREAT;
                } else if (Rc1 == NO && Rc2 == NO) {
                    return SLEEP2_1;
                } else if (Rc1 == me && Rc2 == me) {
                    return RUSH4_2;
                } else if (Rc1 == me || Rc2 == me) {
                    return SLEEP3_1;
                }
            }
            if (Rc == rival) {
                if (Lc1 == rival || Lc2 == rival) {
                    return NOTHREAT;
                } else if (Lc1 == NO && Lc2 == NO) {
                    return SLEEP2_1;
                } else if (Lc1 == me && Lc2 == me) {
                    return RUSH4_2;
                } else if (Lc1 == me || Lc2 == me) {
                    return SLEEP3_1;
                }
            }
        }
    }
    if (count == 1) { //???1?
        int Lc1 = chess[left - 1];
        int Rc1 = chess[right + 1];
        int Lc2 = chess[left - 2];
        int Rc2 = chess[right + 2];
        int Lc3 = chess[left - 3];
        int Rc3 = chess[right + 3];

        if (Lc == NO && Lc1 == me && Lc2 == me && Lc3 == me)
            return RUSH4_2;
        if (Rc == NO && Rc1 == me && Rc2 == me && Rc3 == me)
            return RUSH4_2;

        if (Lc == NO && Lc1 == me && Lc2 == me && Lc3 == NO && Rc == NO)
            return SLEEP3_2;
        if (Rc == NO && Rc1 == me && Rc2 == me && Rc3 == NO && Lc == NO)
            return SLEEP3_2;

        if (Lc == NO && Lc1 == me && Lc2 == me && Lc3 == rival && Rc == NO)
            return SLEEP3_1;
        if (Rc == NO && Rc1 == me && Rc2 == me && Rc3 == rival && Lc == NO)
            return SLEEP3_1;

        if (Lc == NO && Lc1 == NO && Lc2 == me && Lc3 == me)
            return SLEEP3_1;
        if (Rc == NO && Rc1 == NO && Rc2 == me && Rc3 == me)
            return SLEEP3_1;
        if (Lc == NO && Lc1 == me && Lc2 == NO && Lc3 == me)
            return SLEEP3_1;
        if (Rc == NO && Rc1 == me && Rc2 == NO && Rc3 == me)
            return SLEEP3_1;

        if (Lc == NO && Lc1 == me && Lc2 == NO && Lc3 == NO && Rc == NO)
            return SLEEP2_2;
        if (Rc == NO && Rc1 == me && Rc2 == NO && Rc3 == NO && Lc == NO)
            return SLEEP2_2;

        if (Lc == NO && Lc1 == NO && Lc2 == me && Lc3 == NO && Rc == NO)
            return SLEEP2_2;
        if (Rc == NO && Rc1 == NO && Rc2 == me && Rc3 == NO && Lc == NO)
            return SLEEP2_2;
    }
    return NOTHREAT;
}

Point AI::MaxScore(const int MyScore[15][15], const int RivalScore[15][15])
{
    Point point = {0, 0};

    int mymaxscore = 0;
    int hismaxscore = 0;

    std::vector<Point> mypointvector;
    std::vector<Point> hispointvector;

    for (int i = 0; i < 15; i++)
        for (int j = 0; j < 15; j++) {
            if (MyScore[i][j] == mymaxscore) {
                point.x = i;
                point.y = j;
                mypointvector.push_back(point);
            }
            if (MyScore[i][j] > mymaxscore) {
                mymaxscore = MyScore[i][j];
                mypointvector.clear();

                point.x = i;
                point.y = j;
                mypointvector.push_back(point);
            }
        }

    for (int i = 0; i < 15; i++)
        for (int j = 0; j < 15; j++) {
            if (RivalScore[i][j] == hismaxscore) {
                point.x = i;
                point.y = j;
                hispointvector.push_back(point);
            }
            if (RivalScore[i][j] > hismaxscore) {
                hismaxscore = RivalScore[i][j];
                hispointvector.clear();

                point.x = i;
                point.y = j;
                hispointvector.push_back(point);
            }
        }

    if (mymaxscore >= hismaxscore) {
        int temp = 0;

        std::vector<Point>::iterator iter;
        for (iter = mypointvector.begin(); iter != mypointvector.end(); iter++) {
            Point maxtemp = *iter;
            if (RivalScore[maxtemp.x][maxtemp.y] >= temp) {
                temp = RivalScore[maxtemp.x][maxtemp.y];
                point = maxtemp;
            }
        }
        return point;
    } else {
        int temp = 0;

        std::vector<Point>::iterator iter;
        for (iter = hispointvector.begin(); iter != hispointvector.end(); iter++) {
            Point maxtemp = *iter;
            if (MyScore[maxtemp.x][maxtemp.y] >= temp) {
                temp = MyScore[maxtemp.x][maxtemp.y];
                point = maxtemp;
            }
        }
        return point;
    }
}
