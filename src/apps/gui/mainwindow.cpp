#include "mainwindow.h"

namespace App
{

    MainWindow::MainWindow(QWidget *parent)
        : QMainWindow(parent), Ui::MainWindow()
    {
        // UI setup
        setupUi(this);
    }

    MainWindow::~MainWindow()
    {
    }

}

