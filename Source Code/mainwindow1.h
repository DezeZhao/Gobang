#ifndef MAINWINDOW1_H
#define MAINWINDOW1_H
#include "mainwindow.h"
#include <QButtonGroup>
#include <QMainWindow>

namespace Ui {
class MainWindow1;
}

class MainWindow1 : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow1(QWidget *parent = nullptr);
    int mode, fp;
    int flag1 = 0, flag2 = 0, flag3 = 0, flag4 = 0, flag5 = 0, flag6 = 0;
    ~MainWindow1();

private slots:

    void on_radioButton_clicked(bool checked);

    void on_radioButton_2_clicked(bool checked);

    void on_pushButton_2_clicked();

    void on_checkBox_clicked(bool checked);

    void on_checkBox_2_clicked(bool checked);

    void on_radioButton_3_clicked(bool checked);

    void on_radioButton_4_clicked(bool checked);

private:
    Ui::MainWindow1 *ui;
    MainWindow *m = new MainWindow;
};

#endif // MAINWINDOW1_H
