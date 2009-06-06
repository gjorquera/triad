#pragma once

#include <Euclid/Geometry/TriMesh.h>
#include <Viewer/Widget.h>
#include "Kernel.h"

namespace App
{

    class MeshViewer : public Viewer::Widget
    {
        Q_OBJECT

    public:
        MeshViewer(QWidget* parent = 0);
        virtual ~MeshViewer();
        void set(Euclid::TriMesh<Kernel>* trimesh);

    protected:
        void initializeGL();
        void resizeGL(int with, int height);
    };
}

