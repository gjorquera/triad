#include <Viewer/Initializer.h>
#include <Viewer/OrthoProjection.h>
#include "MainWindow.h"
#include "Figure/Triangle.h"

namespace App
{

    MainWindow::MainWindow(QWidget* parent)
        : QMainWindow(parent), Ui::MainWindow()
    {
        // UI setup
        setupUi(this);

        Viewer::Initializer* initializer;
        initializer = new Viewer::Initializer();
        Viewer::Projection* projection;
        projection = new Viewer::OrthoProjection(0.0, 10.0);

        _viewerWidget = new Viewer::Widget(initializer, projection, this);
        this->setCentralWidget(_viewerWidget);

        Triangle* t = new Triangle();
        _viewerWidget->add(t);
    }

    MainWindow::~MainWindow()
    {
    }

}

