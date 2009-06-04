#pragma once

#include <memory>
#include <QMainWindow>
#include <Euclid/Geometry/TriMesh.h>
#include <Euclid/Type/DefaultKernel.h>
#include <Viewer/Widget.h>
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
        MainWindow(QWidget* parent = 0);
        ~MainWindow();

    protected slots:
        void openMesh();
        void saveMesh();

    private:
        Euclid::TriMesh<Euclid::DefaultKernel> _trimesh;
        Viewer::Widget* _viewerWidget;
    };

}

