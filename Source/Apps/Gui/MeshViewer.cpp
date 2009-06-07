#include "MeshViewer.h"
#include "TriangleFigure.h"

namespace App
{

    MeshViewer::MeshViewer(QWidget* parent)
        : Viewer::Widget(parent)
    {
    }

    /*virtual*/
    MeshViewer::~MeshViewer()
    {
    }

    void
    MeshViewer::set(Euclid::TriMesh<Kernel>* trimesh)
    {
        clear();
        Euclid::TriMesh<Kernel>::ConstIterator i;
        for (i = trimesh->begin(); i != trimesh->end(); i++)
        {
            TriangleFigure* figure = new TriangleFigure(*i);
            add(figure);
        }
    }

    void
    MeshViewer::clearSelection()
    {
        Viewer::Widget::Iterator i;
        for (i = begin(); i != end(); i++)
        {
            TriangleFigure* tf = dynamic_cast<TriangleFigure*>(*i);
            tf->triangle()->info().selected = false;
            tf->triangle()->info().lepp = false;
        }
    }

    void
    MeshViewer::paintGL()
    {
        /// @todo Set lepp = false
        /// @todo Calculate lepp based on selected triangles
        Viewer::Widget::paintGL();
    }

    void
    MeshViewer::initializeGL()
    {
        glClearColor(1.0, 1.0, 1.0, 1.0);
        glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_LINE_SMOOTH);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
    }

    void
    MeshViewer::viewportGL(int width, int height)
    {
        glViewport(0, 0, width, height);
    }

    void
    MeshViewer::projectionGL(int, int)
    {
        glOrtho(0, 10, 0, 10, 0, 10);
    }
}

