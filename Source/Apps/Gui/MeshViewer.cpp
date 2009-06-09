#include <QListIterator>
#include "Algorithm/LeppStrategy.h"
#include "MeshViewer.h"
#include "TriangleFigure.h"

namespace App
{

    MeshViewer::MeshViewer(QWidget* parent)
        : Viewer::Widget(parent)
    {
        _leppStrat = 0;
    }

    /*virtual*/
    MeshViewer::~MeshViewer()
    {
        if (0 != _leppStrat) delete _leppStrat;
    }

    void
    MeshViewer::set(Euclid::TriMesh<Kernel>* trimesh)
    {
        clear();
        QListIterator<Euclid::Triangle<Kernel>*> i(trimesh->triangles());
        while (i.hasNext())
        {
            TriangleFigure* figure = new TriangleFigure(i.next());
            add(figure);
        }
    }

    void
    MeshViewer::setStrategy(LeppStrategy* leppStrat)
    {
        _leppStrat = leppStrat;
    }

    void
    MeshViewer::clearSelection()
    {
        QListIterator<Viewer::Figure*> i(figures());
        while (i.hasNext())
        {
            TriangleFigure* tf = dynamic_cast<TriangleFigure*>(i.next());
            tf->triangle()->info().selected = false;
            tf->triangle()->info().lepp = false;
        }
    }

    void
    MeshViewer::paintGL()
    {
        QListIterator<Viewer::Figure*> i(figures());
        while (i.hasNext())
        {
            TriangleFigure* tf = dynamic_cast<TriangleFigure*>(i.next());
            tf->triangle()->info().lepp = false;
        }
        if (0 != _leppStrat) {
            _leppStrat->highlightLepp();
        }
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

