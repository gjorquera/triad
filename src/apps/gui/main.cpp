// Debugging
#include <iostream>

#include <QtGui/QApplication>
#include "mainwindow.h"

int
main(int argc, char* argv[])
{
    QApplication a(argc, argv);
    App::MainWindow w;
    w.showMaximized();
    return a.exec();
}

