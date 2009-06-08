#include <QFileDialog>
#include <Euclid/Algorithm/LongestEdgeCriterion.h>
#include <Euclid/Geometry/M2dFormatIO.h>
#include "MainWindow.h"
#include "Dialog/LongestEdgeDialog.h"

namespace App
{

    bool MainWindow::viewNeighbors;
    bool MainWindow::viewLepp;

    MainWindow::MainWindow(QWidget* parent)
        : QMainWindow(parent), Ui::MainWindow()
    {
        setupUi(this);

        _longestEdgeDialog = new LongestEdgeDialog(this);

        MainWindow::viewNeighbors = true;
        MainWindow::viewLepp = true;
        _trimesh = new TriMesh;
        _meshViewer = new MeshViewer(this);
        this->setCentralWidget(_meshViewer);

        connect(actionOpenMesh, SIGNAL(triggered()),
            this, SLOT(openMesh()));
        connect(actionSaveMesh, SIGNAL(triggered()),
            this, SLOT(saveMesh()));
        connect(actionManualSelection, SIGNAL(toggled(bool)),
            _meshViewer, SLOT(setPicking(bool)));
        connect(actionByLongestEdge, SIGNAL(triggered()),
            this, SLOT(selectByLongestEdge()));
        connect(actionClearSelection, SIGNAL(triggered()),
            _meshViewer, SLOT(clearSelection()));
        connect(actionNeighbors, SIGNAL(toggled(bool)),
            this, SLOT(setViewNeighbors(bool)));
        connect(actionLepp, SIGNAL(toggled(bool)),
            this, SLOT(setViewLepp(bool)));
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
            delete _trimesh;
            _trimesh = new TriMesh;
            Euclid::M2dFormatIO<Kernel> meshLoader(filename, _trimesh);
            meshLoader.load();
            _meshViewer->set(_trimesh);
            NaiveLeppStrategy* leppStrat = new NaiveLeppStrategy(_trimesh);
            _meshViewer->setStrategy(leppStrat);
        }

        _meshViewer->updateGL();
    }

    void
    MainWindow::saveMesh()
    {
        QString filename = QFileDialog::getSaveFileName(this,
            tr("Save Mesh File"), QDir::currentPath(), tr("M2D File (*.m2d)"));

        if (0 != filename) {
            Euclid::M2dFormatIO<Kernel> meshSaver(filename, _trimesh);
            meshSaver.save();
        }
    }

    void
    MainWindow::selectByLongestEdge()
    {
        if (_longestEdgeDialog->exec()) {
            float max = _longestEdgeDialog->dsbMaximum->value();
            bool biggest = _longestEdgeDialog->rbtBigger->isChecked();
            Euclid::LongestEdgeCriterion<Kernel> c(max, biggest);
            _trimesh->select(c);
            _meshViewer->updateGL();
        }
    }

    void
    MainWindow::setViewNeighbors(bool viewNeighbors)
    {
        MainWindow::viewNeighbors = viewNeighbors;
        _meshViewer->updateGL();
    }

    void
    MainWindow::setViewLepp(bool viewLepp)
    {
        MainWindow::viewLepp = viewLepp;
        _meshViewer->updateGL();
    }
}

