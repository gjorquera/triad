#include <QFileDialog>
#include <Euclid/Geometry/M2dFactory.h>
#include "MainWindow.h"

namespace App
{

    MainWindow::MainWindow(QWidget* parent)
        : QMainWindow(parent), Ui::MainWindow()
    {
        setupUi(this);

        _trimesh = 0;
        _meshViewer = new MeshViewer(this);
        this->setCentralWidget(_meshViewer);

        connect(actionOpenMesh, SIGNAL(triggered()), this, SLOT(openMesh()));
        connect(actionSaveMesh, SIGNAL(triggered()), this, SLOT(saveMesh()));
        connect(actionManualSelection, SIGNAL(toggled(bool)),
            _meshViewer, SLOT(setPicking(bool)));
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
            _meshViewer->set(_trimesh);
        }

        _meshViewer->updateGL();
    }

    void
    MainWindow::saveMesh()
    {
        QString filename = QFileDialog::getSaveFileName(this,
            tr("Save Mesh File"), QDir::currentPath(), tr("M2D File (*.m2d)"));

        if (0 != filename) {
            /// @todo Save mesh.
        }

        _meshViewer->updateGL();
    }
}

