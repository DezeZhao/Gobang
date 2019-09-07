#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <QBrush>
#include <QMessageBox>
#include <QMouseEvent>
#include <QPainter>
#include <QPalette>
#include <QPen>
#include <QTimer>
using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}
void MainWindow::paintEvent(QPaintEvent *)
{
    /*draw the chess pad and five black point*/
    this->setFixedSize(640, 660);
    this->setAutoFillBackground(true);
    QPalette palette;
    palette.setColor(QPalette::Background, QColor("#B1723C"));
    this->setPalette(palette);
    centralWidget()->setMouseTracking(true);
    setMouseTracking(true);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);

    QPen pen = painter.pen();
    pen.setColor(QColor("#8D5822"));
    pen.setWidth(7);
    painter.setPen(pen);

    QBrush brush;
    brush.setColor("#EEC085");
    brush.setStyle(Qt::SolidPattern);
    painter.setBrush(brush);
    painter.drawRect(20, 40, 600, 600);

    pen.setColor(Qt::black);
    pen.setWidth(1);
    painter.setPen(pen);
    for (int i = 0; i < 15; i++) {
        painter.drawLine(40 + i * 40, 60, 40 + i * 40, 620);
        painter.drawLine(40, 60 + i * 40, 600, 60 + i * 40);
    }
    brush.setColor(Qt::black);
    painter.setBrush(brush);
    painter.drawRect(155, 175, 10, 10);
    painter.drawRect(475, 175, 10, 10);
    painter.drawRect(155, 495, 10, 10);
    painter.drawRect(475, 495, 10, 10);
    painter.drawRect(315, 335, 10, 10);
    /*end of draw the chess pad and five black point*/

    //judge if it is PEvsAI mode
    if (PvAflag == 1) {
        AI_Chess();
        PvAflag = 0;
    }

    /*paint four red corner*/
    pen.setColor(Qt::red);
    pen.setWidth(1);
    painter.setPen(pen);
    if ((moveX * 40 + 40) >= 0 && (moveX * 40 + 40) <= 600 && (moveY * 40 + 20) >= 0
        && (moveY * 40 + 20) <= 600) {
        painter.drawLine((moveY + 1) * 40 - 20,
                         (moveX + 1) * 40,
                         (moveY + 1) * 40 - 10,
                         (moveX + 1) * 40);
        painter.drawLine((moveY + 1) * 40 + 20,
                         (moveX + 1) * 40,
                         (moveY + 1) * 40 + 10,
                         (moveX + 1) * 40);
        painter.drawLine((moveY + 1) * 40 - 20,
                         (moveX + 1) * 40 + 40,
                         (moveY + 1) * 40 - 10,
                         (moveX + 1) * 40 + 40);
        painter.drawLine((moveY + 1) * 40 + 20,
                         (moveX + 1) * 40 + 40,
                         (moveY + 1) * 40 + 10,
                         (moveX + 1) * 40 + 40);
        painter.drawLine((moveY + 1) * 40 - 20,
                         (moveX + 1) * 40,
                         (moveY + 1) * 40 - 20,
                         (moveX + 1) * 40 + 10);
        painter.drawLine((moveY + 1) * 40 + 20,
                         (moveX + 1) * 40,
                         (moveY + 1) * 40 + 20,
                         (moveX + 1) * 40 + 10);
        painter.drawLine((moveY + 1) * 40 - 20,
                         (moveX + 1) * 40 + 40,
                         (moveY + 1) * 40 - 20,
                         (moveX + 1) * 40 + 30);
        painter.drawLine((moveY + 1) * 40 + 20,
                         (moveX + 1) * 40 + 40,
                         (moveY + 1) * 40 + 20,
                         (moveX + 1) * 40 + 30);
    }

    //paint the pe or AI 's chess
    chessboard.GetChessStatus(Status);
    if (Status[currentX][currentY] == 2) {
        brush.setColor(Qt::white);
        painter.setBrush(brush);
        painter.drawEllipse(QPoint((currentY + 1) * 40, (currentX + 1) * 40 + 20), 18, 18);
    }
    if (Status[currentX][currentY] == 1) {
        brush.setColor(Qt::black);
        painter.setBrush(brush);
        painter.drawEllipse(QPoint((currentY + 1) * 40, (currentX + 1) * 40 + 20), 18, 18);
    }

    //paint the + in the center of chess
    pen.setColor((Qt::red));
    pen.setWidth(1);
    painter.setPen(pen);
    painter.drawLine((currentY + 1) * 40 - 1,
                     (currentX + 1) * 40 + 20,
                     (currentY + 1) * 40 - 6,
                     (currentX + 1) * 40 + 20);
    painter.drawLine((currentY + 1) * 40 + 1,
                     (currentX + 1) * 40 + 20,
                     (currentY + 1) * 40 + 6,
                     (currentX + 1) * 40 + 20);
    painter.drawLine((currentY + 1) * 40,
                     (currentX + 1) * 40 + 19,
                     (currentY + 1) * 40,
                     (currentX + 1) * 40 + 14);
    painter.drawLine((currentY + 1) * 40,
                     (currentX + 1) * 40 + 21,
                     (currentY + 1) * 40,
                     (currentX + 1) * 40 + 26);

    /*get current chesspad status and paint again*/
    chessboard.GetChessStatus(Status);
    for (int i = 0; i < 15; i++)
        for (int j = 0; j < 15; j++) {
            if (Status[i][j] == 0)
                continue;
            else if (Status[i][j] == 1) {
                brush.setColor(Qt::black);
                painter.setBrush(brush);
                painter.drawEllipse(QPoint((j + 1) * 40, (i + 1) * 40 + 20), 18, 18);
            } else if (Status[i][j] == 2) {
                brush.setColor(Qt::white);
                painter.setBrush(brush);
                painter.drawEllipse(QPoint((j + 1) * 40, (i + 1) * 40 + 20), 18, 18);
            } else if (Status[i][j] == 3) {
                brush.setColor(Qt::black);
                painter.setBrush(brush);
                painter.drawEllipse(QPoint((j + 1) * 40, (i + 1) * 40 + 20), 18, 18);
                pen.setColor((Qt::red));
                pen.setWidth(1);
                painter.setPen(pen);
                painter.drawLine((j + 1) * 40 - 1,
                                 (i + 1) * 40 + 20,
                                 (j + 1) * 40 - 6,
                                 (i + 1) * 40 + 20);
                painter.drawLine((j + 1) * 40 + 1,
                                 (i + 1) * 40 + 20,
                                 (j + 1) * 40 + 6,
                                 (i + 1) * 40 + 20);
                painter.drawLine((j + 1) * 40, (i + 1) * 40 + 19, (j + 1) * 40, (i + 1) * 40 + 14);
                painter.drawLine((j + 1) * 40, (i + 1) * 40 + 21, (j + 1) * 40, (i + 1) * 40 + 26);
            } else if (Status[i][j] == 4) {
                brush.setColor(Qt::white);
                painter.setBrush(brush);
                painter.drawEllipse(QPoint((j + 1) * 40, (i + 1) * 40 + 20), 18, 18);
                pen.setColor((Qt::red));
                pen.setWidth(1);
                painter.setPen(pen);
                painter.drawLine((j + 1) * 40 - 1,
                                 (i + 1) * 40 + 20,
                                 (j + 1) * 40 - 6,
                                 (i + 1) * 40 + 20);
                painter.drawLine((j + 1) * 40 + 1,
                                 (i + 1) * 40 + 20,
                                 (j + 1) * 40 + 6,
                                 (i + 1) * 40 + 20);
                painter.drawLine((j + 1) * 40, (i + 1) * 40 + 19, (j + 1) * 40, (i + 1) * 40 + 14);
                painter.drawLine((j + 1) * 40, (i + 1) * 40 + 21, (j + 1) * 40, (i + 1) * 40 + 26);
            }
        }

    //judge result
    int result;
    result = judge.JudgeResult(Status);
    if (result == 1) {
        QMessageBox::information(this, "tip", "black win!");
        exit(0);
    } else if (result == 2) {
        QMessageBox::information(this, "tip", "white win!");
        exit(0);
    } else if (result == 3) {
        QMessageBox::information(this, "tip", "you are drew!");
        exit(0);
    }
}
void MainWindow::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        currentX = moveX;
        currentY = moveY;
        if (mode == 0)
            PE_Chess();
        else if (mode == 1) {
            player = !player;
            PE_Chess();
        }
    }
}
void MainWindow::mouseReleaseEvent(QMouseEvent *)
{
    currentX = moveX;
    currentY = moveY;
    //QTimer::singleShot(700, this, SLOT(AI_Chess()));//AI think time
    if (mode == 0)
        AI_Chess();
    update();
}
void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    moveX = (event->y() - 40) / 40;
    moveY = (event->x() - 20) / 40;
    update();
}
void MainWindow::AI_Chess() //ai's turn to add a chess
{
    if (mode == 0 && fp == 0) {
        AI_Chesser ai(0);                //ai is black
        if (!(judge.JudgeNextChesser())) //curchesser=0 ,ai'turn==black's turn
            chessboard.AddChess(ai.GiveNextChess(Status, currentX, currentY));
    }
    if (mode == 0 && fp == 1) {
        AI_Chesser ai(1);             //ai is white
        if (judge.JudgeNextChesser()) //curchesser=1, ai's turn==white's turn
            chessboard.AddChess(ai.GiveNextChess(Status, currentX, currentY));
    }
    update();
}
void MainWindow::PE_Chess() //pe's turn to add a chess
{
    if (Status[currentX][currentY] == 0) {
        if ((mode == 0 && fp == 0) || (mode == 1 && fp == 1 && player == 1)) {
            PE_Chesser pe(1);             //pe is white
            if (judge.JudgeNextChesser()) //1,curchesser=1,pe's turn==white's turn
                chessboard.AddChess(pe.GiveNextChess(currentX, currentY));
        }
        if ((mode == 0 && fp == 1) || (mode == 1 && fp == 0 && player == 0)) {
            PE_Chesser pe(0);                //pe is black
            if (!(judge.JudgeNextChesser())) //0,curchesser=0,pe's turn==black's turn
                chessboard.AddChess(pe.GiveNextChess(currentX, currentY));
        }
        if (mode == 1 && fp == 0 && player == 1) {
            PE_Chesser pe1(1); //pe1 is white
            if (judge.JudgeNextChesser())
                chessboard.AddChess(pe1.GiveNextChess(currentX, currentY));
        }
        if (mode == 1 && fp == 1 && player == 0) {
            PE_Chesser pe1(0); //pe1 is black
            if (!(judge.JudgeNextChesser()))
                chessboard.AddChess(pe1.GiveNextChess(currentX, currentY));
        }
        update();
    }
}
MainWindow::~MainWindow()
{
    delete ui;
}
