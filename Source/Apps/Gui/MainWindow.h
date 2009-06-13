#pragma once

#include <memory>
#include <QMainWindow>
#include <Euclid/Algorithm/Strategy.h>
#include "TriMesh.h"
#include "Kernel.h"
#include "MeshViewer.h"
#include "ui_MainWindow.h"

namespace App
{

    class LongestEdgeDialog;
    class PercentageDialog;

    /*!
     * The application's main window.
     */
    class MainWindow : public QMainWindow, public Ui::MainWindow
    {
        Q_OBJECT

    public:
        static bool viewNeighbors;
        static bool viewLepp;

        MainWindow(QWidget* parent = 0);
        ~MainWindow();
        void setStatusbarMessage();

    protected slots:
        void openMesh();
        void saveMesh();
        void selectByLongestEdge();
        void selectByPercentage();
        void setViewNeighbors(bool viewNeighbor);
        void setViewLepp(bool viewLepp);
        void setLeppRefinement();
        void executeRefinement();

    private:
        TriMesh* _trimesh;
        MeshViewer* _meshViewer;
        LongestEdgeDialog* _longestEdgeDialog;
        PercentageDialog* _percentageDialog;
        Euclid::Strategy<Kernel>* _refineStrat;
    };

}

