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
        void setViewNeighbors(bool viewNeighbor);
        void setViewLepp(bool viewLepp);
        void setLeppRefinement();
        void setParallelLeppRefinement();
        void executeRefinement();

    private:
        TriMesh* _trimesh;
        MeshViewer* _meshViewer;
        LongestEdgeDialog* _longestEdgeDialog;
        Euclid::Strategy<Kernel>* _refineStrat;
    };

}

