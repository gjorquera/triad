#include <Viewer/FigureIterator.h>
#include "Algorithm/NaiveLeppStrategy.h"
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
        Euclid::TriMesh<Kernel>::ConstIterator i;
        for (i = trimesh->begin(); i != trimesh->end(); i++)
        {
            TriangleFigure* figure = new TriangleFigure(*i);
            add(figure);
        }
    }

    void
    MeshViewer::setStrategy(NaiveLeppStrategy* leppStrat)
    {
        _leppStrat = leppStrat;
    }

    void
    MeshViewer::clearSelection()
    {
        Viewer::FigureIterator i(*this);
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
        Viewer::FigureIterator i(*this);
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

