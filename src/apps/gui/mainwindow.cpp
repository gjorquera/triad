#include <Viewer/OrthographicProjection.h>
#include "mainwindow.h"

namespace App
{

    MainWindow::MainWindow(QWidget *parent)
        : QMainWindow(parent), Ui::MainWindow()
    {
        // UI setup
        setupUi(this);

        Viewer::Projection *projection;
        projection = new Viewer::OrthographicProjection(0.0, 1.0);

        _viewerWidget = new Viewer::Widget(projection, this);
        this->setCentralWidget(_viewerWidget);
    }

    MainWindow::~MainWindow()
    {
    }

}

