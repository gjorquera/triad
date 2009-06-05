#include <QFileDialog>
#include <Euclid/Geometry/M2dFactory.h>
#include <Viewer/Initializer.h>
#include <Viewer/OrthoProjection.h>
#include "MainWindow.h"
#include "Figure/TriangleDecorator.h"

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

        connect(actionOpenMesh, SIGNAL(triggered()), this, SLOT(openMesh()));
        connect(actionSaveMesh, SIGNAL(triggered()), this, SLOT(saveMesh()));
    }

    MainWindow::~MainWindow()
    {
    }

    void
    MainWindow::openMesh()
    {
        QString filename = QFileDialog::getOpenFileName(this,
            tr("Open Mesh File"), QDir::currentPath(), tr("M2D File (*.m2d)"));

        if (0 != filename) {
            if (0 != _trimesh) delete _trimesh;
            Euclid::M2dFactory<Kernel> m2dFactory(filename.toStdString());
            _trimesh = m2dFactory.load();
        }

        /// @todo Update the OpenGL widget
        //this->redraw();
    }

    void
    MainWindow::saveMesh()
    {
        QString filename = QFileDialog::getSaveFileName(this,
            tr("Save Mesh File"), QDir::currentPath(), tr("M2D File (*.m2d)"));

        if (0 != filename) {
            /// @todo Save mesh.
        }
    }
}

