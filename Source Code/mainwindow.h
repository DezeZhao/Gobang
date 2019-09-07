#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "AI_Chesser.h"
#include "ChessBoard.h"
#include "Judge.h"
#include "PE_Chesser.h"
#include <QMainWindow>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    int fp;   //first player
    int mode; //game mode
    int PvAflag = 0;
    explicit MainWindow(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *);
    void mousePressEvent(QMouseEvent *);
    int player;
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    Judge judge;
    ChessBoard chessboard;
    int Status[15][15] = {{0}};

    int moveX, moveY, currentX, currentY; //mouse move position
private slots:
    void PE_Chess();
    void AI_Chess();
};
#endif
