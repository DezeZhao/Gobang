#include "mainwindow.h"
#include "mainwindow1.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow1 w1;
    w1.show();
    return a.exec();
}
