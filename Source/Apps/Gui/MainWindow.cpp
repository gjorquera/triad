#include <QFileDialog>
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

        connect(actionOpenMesh, SIGNAL(triggered()), this, SLOT(open()));
        connect(actionSaveMesh, SIGNAL(triggered()), this, SLOT(save()));
    }

    MainWindow::~MainWindow()
    {
    }

    void
    MainWindow::open()
    {
        QString filename = QFileDialog::getOpenFileName(this,
            tr("Open Mesh File"), QDir::currentPath(), tr("M2D File (*.m2d)"));

        if (0 != filename) {
            /// @todo Load the saved mesh.
            //if (0 != this->m_trimesh) delete this->m_trimesh;
            //Euclid::M2dFactory<Kernel> m2dFactory(filename.toStdString());
            //this->m_trimesh = m2dFactory.load();
        }

        /// @todo Update the OpenGL widget
        //this->redraw();
    }

    void
    MainWindow::save()
    {
        QString filename = QFileDialog::getSaveFileName(this,
            tr("Save Mesh File"), QDir::currentPath(), tr("M2D File (*.m2d)"));

        if (0 != filename) {
            /// @todo Save mesh.
        }
    }
}

