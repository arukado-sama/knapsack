#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;
    w.show();

    //set window title
    w.setWindowTitle("KNAPSACK v0.3");

    return a.exec();
}
