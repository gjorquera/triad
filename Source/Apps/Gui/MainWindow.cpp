#include <QFileDialog>
#include <Euclid/Algorithm/LongestEdgeCriterion.h>
#include <Euclid/Algorithm/PercentageCriterion.h>
#include <Euclid/Geometry/M2dFormatIO.h>
#include "MainWindow.h"
#include "Algorithm/LeppStrategy.h"
#include "Algorithm/SelectedCriterion.h"
#include "Dialog/LongestEdgeDialog.h"
#include "Dialog/PercentageDialog.h"

namespace App
{

    bool MainWindow::viewNeighbors;
    bool MainWindow::viewLepp;

    MainWindow::MainWindow(QWidget* parent)
        : QMainWindow(parent), Ui::MainWindow()
    {
        setupUi(this);

        _longestEdgeDialog = new LongestEdgeDialog(this);
        _percentageDialog = new PercentageDialog(this);

        MainWindow::viewNeighbors = true;
        MainWindow::viewLepp = true;
        _trimesh = new TriMesh;
        _meshViewer = new MeshViewer(this);
        this->setCentralWidget(_meshViewer);

        _refineStrat = new LeppStrategy;

        connect(actionOpenMesh, SIGNAL(triggered()),
            this, SLOT(openMesh()));
        connect(actionSaveMesh, SIGNAL(triggered()),
            this, SLOT(saveMesh()));
        connect(actionManualSelection, SIGNAL(toggled(bool)),
            _meshViewer, SLOT(setPicking(bool)));
        connect(actionByLongestEdge, SIGNAL(triggered()),
            this, SLOT(selectByLongestEdge()));
        connect(actionByPercentage, SIGNAL(triggered()),
            this, SLOT(selectByPercentage()));
        connect(actionClearSelection, SIGNAL(triggered()),
            _meshViewer, SLOT(clearSelection()));
        connect(actionNeighbors, SIGNAL(toggled(bool)),
            this, SLOT(setViewNeighbors(bool)));
        connect(actionLepp, SIGNAL(toggled(bool)),
            this, SLOT(setViewLepp(bool)));
        connect(actionSecuentialLeppBisection, SIGNAL(triggered()),
            this, SLOT(setLeppRefinement()));
        connect(actionParallelLeppBisection, SIGNAL(triggered()),
            this, SLOT(setParallelLeppRefinement()));
        connect(actionExecute, SIGNAL(triggered()),
            this, SLOT(executeRefinement()));
    }

    MainWindow::~MainWindow()
    {
    }

    void
    MainWindow::setStatusbarMessage()
    {
        LeppStrategy lepp(_trimesh);
        QString status = "Loaded trimesh with %1 vertice(s), %2 triangle(s)"
            " and %3 average lepp, using %4 kb memory";
        statusbar->showMessage(status.arg(_trimesh->numVertices())
            .arg(_trimesh->numTriangles())
            .arg(lepp.averageLepp())
            .arg(_trimesh->memory() / 1024));
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
            LeppStrategy* leppStrat = new LeppStrategy(_trimesh);
            _meshViewer->setStrategy(leppStrat);
            setStatusbarMessage();
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
    MainWindow::selectByPercentage()
    {
        if (_percentageDialog->exec()) {
            int percentage = _percentageDialog->spbPercentage->value();
            bool biggest = _percentageDialog->rbtBigger->isChecked();
            Euclid::PercentageCriterion<Kernel> c(_trimesh->triangles(),
                percentage, biggest);
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

    void
    MainWindow::setLeppRefinement()
    {
        _refineStrat = new LeppStrategy;
    }

    void
    MainWindow::setParallelLeppRefinement()
    {
        /// @todo _refineStrat = new ParallelLeppStrategy;
    }

    void
    MainWindow::executeRefinement()
    {
        assert(0 != _refineStrat);
        SelectedCriterion sc;
        _refineStrat->setTriMesh(_trimesh);
        _refineStrat->refine(sc);
        _meshViewer->set(_trimesh);
        _meshViewer->updateGL();
        setStatusbarMessage();
    }
}

