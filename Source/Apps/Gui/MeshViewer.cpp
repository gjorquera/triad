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
    MeshViewer::resizeGL(int width, int height)
    {
        glViewport(0, 0, width, height);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(0, 10, 0, 10, 0, 10);
        glMatrixMode(GL_MODELVIEW);
    }
}

