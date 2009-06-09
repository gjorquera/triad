#pragma once

#include <Euclid/Geometry/TriMesh.h>
#include <Viewer/Widget.h>
#include "Algorithm/LeppStrategy.h"
#include "Kernel.h"

namespace App
{

    /*!
     * The MeshViewer class defines a custom implementation of the
     * Viewer::Widget class.
     *
     * This class implements the custom OpenGL \b initializeGL and \b resizeGL
     * (viewport and projections) as well as implementing a method to \b set the
     * widget figures based on an Euclid::TriMesh.
     */
    class MeshViewer : public Viewer::Widget
    {
        Q_OBJECT

    public:
        MeshViewer(QWidget* parent = 0);
        virtual ~MeshViewer();
        void set(Euclid::TriMesh<Kernel>* trimesh);
        void setStrategy(LeppStrategy* leppStrat);

    public slots:
        void clearSelection();

    protected:
        void paintGL();
        void initializeGL();
        void viewportGL(int width, int height);
        void projectionGL(int width, int height);

    private:
        LeppStrategy* _leppStrat;
    };
}

