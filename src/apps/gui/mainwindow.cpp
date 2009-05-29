#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), Ui::MainWindow()
{
    // UI setup
    setupUi(this);
}

MainWindow::~MainWindow()
{
}

