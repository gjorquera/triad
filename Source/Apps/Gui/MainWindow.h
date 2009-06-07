#pragma once

#include <memory>
#include <QMainWindow>
#include <Euclid/Geometry/TriMesh.h>
#include "Kernel.h"
#include "MeshViewer.h"
#include "ui_MainWindow.h"

namespace App
{

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

    protected slots:
        void openMesh();
        void saveMesh();
        void setViewNeighbors(bool viewNeighbor);
        void setViewLepp(bool viewLepp);

    private:
        Euclid::TriMesh<Kernel>* _trimesh;
        MeshViewer* _meshViewer;
    };

}

