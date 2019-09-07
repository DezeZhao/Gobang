#include "Judge.h"
Judge::Judge()
{
    CurChesser = 1; //white fang
}

int Judge::JudgeResult(const int chesspadstate[15][15])
{
    int lastrow, lastcolumn;
    int i, j;
    int count, result;
    int rowmin, rowmax, columnmin, columnmax;

    int flag = 0;
    for (i = 0; i < 15; i++) {
        for (j = 0; j < 15; j++) {
            if (chesspadstate[i][j] == 0) {
                flag = 1;
                break;
            }
        }
        if (flag)
            break;
    }
    if (i == 15 && j == 15)
        return 3; //�;�

    flag = 0;
    for (i = 0; i < 15; i++) { //���һ��������
        for (j = 0; j < 15; j++)
            if (chesspadstate[i][j] > 2) {
                lastrow = i;
                lastcolumn = j;
                result = chesspadstate[i][j] - 2; //���ص�ǰ����Ӯ�ı�־
                flag = 1;
                break;
            }
        if (flag)
            break;
    }
    if (i == 15 && j == 15) //��û��ʼ����
        return 0;

    //����
    count = 0;
    columnmin = lastcolumn - 4 < 0 ? 0 : lastcolumn - 4;
    columnmax = lastcolumn + 4 > 14 ? 14 : lastcolumn + 4;
    for (i = lastrow, j = columnmin; j <= columnmax; j++) {
        if (chesspadstate[i][j] == result
            || chesspadstate[i][j] == result + 2) { //���ؽ����־�����־��ͬ
            count++;
            if (count == 5) //Ӯ��
                return result;
        } else
            count = 0; //��ͷ����
    }

    //����
    count = 0;
    rowmin = lastrow - 4 < 0 ? 0 : lastrow - 4;
    rowmax = lastrow + 4 > 14 ? 14 : lastrow + 4;
    for (i = rowmin, j = lastcolumn; i <= rowmax; i++) {
        if (chesspadstate[i][j] == result
            || chesspadstate[i][j] == result + 2) { //���ؽ����־�����־��ͬ
            count++;
            if (count == 5) //Ӯ��
                return result;
        } else
            count = 0; //��ͷ����
    }

    //����б
    count = 0;
    rowmin = lastrow - 4;
    columnmin = lastcolumn - 4;
    if (rowmin < 0 || columnmin < 0) {     //����
        if (lastrow > lastcolumn) {        //���粽��С�ȳ���
            columnmin = 0;                 //�ȳ����Ϊ�߽�ֵ
            rowmin = lastrow - lastcolumn; //�����ĸ���б��1
        } else {
            rowmin = 0;
            columnmin = lastcolumn - lastrow;
        }
    }
    rowmax = lastrow + 4;
    columnmax = lastcolumn + 4;
    if (rowmax > 14 || columnmax > 14) {      //����
        if (14 - lastrow < 14 - lastcolumn) { //���粽��С�ȳ���
            rowmax = 14;                      //�ȳ����Ϊ�߽�ֵ
            columnmax = lastcolumn + 14 - lastrow;
        } else {
            columnmax = 14;
            rowmax = lastrow + 14 - lastcolumn;
        }
    }
    for (i = rowmin, j = columnmin; i <= rowmax; i++, j++) {
        if (chesspadstate[i][j] == result
            || chesspadstate[i][j] == result + 2) { //���ؽ����־�����־��ͬ
            count++;
            if (count == 5) //Ӯ��
                return result;
        } else
            count = 0; //��ͷ����
    }

    //����б
    count = 0;
    rowmin = lastrow - 4;
    columnmax = lastcolumn + 4;
    if (rowmin < 0 || columnmax > 14) {      //����
        if (lastrow - 0 < 14 - lastcolumn) { //���粽��С�ȳ���
            rowmin = 0;                      //�ȳ���Ϊ�߽�ֵ
            columnmax = lastcolumn + lastrow;
        } else {
            columnmax = 14;
            rowmin = lastrow - (14 - lastcolumn);
        }
    }
    rowmax = lastrow + 4;
    columnmin = lastcolumn - 4;
    if (rowmax > 14 || columnmin < 0) {      //����
        if (14 - lastrow < lastcolumn - 0) { //���粽��С�ȳ���
            rowmax = 14;
            columnmin = lastcolumn - (14 - lastrow);
        } else {
            columnmin = 0;
            rowmax = lastrow + lastcolumn - 0;
        }
    }
    for (i = rowmin, j = columnmax; i <= rowmax; i++, j--) {
        if (chesspadstate[i][j] == result
            || chesspadstate[i][j] == result + 2) { //���ؽ����־�����־��ͬ
            count++;
            if (count == 5) //Ӯ��
                return result;
        } else
            count = 0; //��ͷ����
    }
    return 0; //δ��ʤ��
}

int Judge::JudgeNextChesser()
{
    return CurChesser = (CurChesser == 1) ? 0 : 1;
}