#include "mainwindow.h"

namespace App
{

    MainWindow::MainWindow(QWidget *parent)
        : QMainWindow(parent), Ui::MainWindow()
    {
        // UI setup
        setupUi(this);

        _viewerWidget = new Viewer::Widget(this);
        this->setCentralWidget(_viewerWidget);
    }

    MainWindow::~MainWindow()
    {
    }

}

