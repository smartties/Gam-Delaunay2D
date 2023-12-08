#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication entree(argc, argv);
    MainWindow mWin;
    mWin.show();

    return entree.exec();
}
