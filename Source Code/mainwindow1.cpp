#include "mainwindow1.h"
#include "mainwindow.h"
#include "ui_mainwindow1.h"
#include <iostream>
#include <QTimer>
using namespace std;
MainWindow1::MainWindow1(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow1)
{
    ui->setupUi(this);
    setFixedSize(800, 500);
}

MainWindow1::~MainWindow1()
{
    delete ui;
}
void on_Qbg1_toggled(int, bool) {}
void MainWindow1::on_checkBox_clicked(bool checked)
{
    if (checked) {
        m->mode = 0; //人机
        flag1 = 1;
    }
}
void MainWindow1::on_checkBox_2_clicked(bool checked)
{
    if (checked) {
        m->mode = 1; //人人
        m->player = 1;
        flag2 = 1;
    }
}

void MainWindow1::on_radioButton_clicked(bool checked)
{
    if (checked) {
        m->fp = 0; //AI
        m->PvAflag = 1;
        flag3 = 1;
    }
}

void MainWindow1::on_radioButton_2_clicked(bool checked)
{
    if (checked) {
        m->fp = 1; //PE
        flag5 = 1;
    }
}

void MainWindow1::on_radioButton_3_clicked(bool checked)
{
    if (checked) {
        m->fp = 0;
        flag4 = 1;
    }
}

void MainWindow1::on_radioButton_4_clicked(bool checked)
{
    if (checked) {
        m->fp = 1;
        flag6 = 1;
    }
}
void MainWindow1::on_pushButton_2_clicked()
{
    if ((flag1 == 1 && (flag3 || flag5)) || (flag2 && (flag4 || flag6)))
        m->show();
    else
        ;
}
