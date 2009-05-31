#include <Viewer/Initializer.h>
#include <Viewer/OrthographicProjection.h>
#include "mainwindow.h"
#include "triangle.h"

namespace App
{

    MainWindow::MainWindow(QWidget *parent)
        : QMainWindow(parent), Ui::MainWindow()
    {
        // UI setup
        setupUi(this);

        Viewer::Initializer *initializer;
        initializer = new Viewer::Initializer();
        Viewer::Projection *projection;
        projection = new Viewer::OrthographicProjection(0.0, 1.0);

        _viewerWidget = new Viewer::Widget(initializer, projection, this);
        this->setCentralWidget(_viewerWidget);

        Triangle *t = new Triangle();
        _viewerWidget->add(t);
    }

    MainWindow::~MainWindow()
    {
    }

}

