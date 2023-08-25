#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setFixedSize(709, 501);
    w.setWindowTitle("(._.");
    w.show();
    return a.exec();
}
