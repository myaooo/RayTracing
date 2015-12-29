#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    Color c(0.1,0.2,0.3);
    Color b(0.2,0.3,0.4);
    Color d = c+b;
    return a.exec();
}
