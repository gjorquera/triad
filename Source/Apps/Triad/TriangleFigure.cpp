#include <Viewer/ComplexDecorator.h>
#include "MainWindow.h"
#include "TriangleFigure.h"
#include "Decorator/LeppDecorator.h"
#include "Decorator/NeighborDecorator.h"
#include "Decorator/NormalDecorator.h"
#include "Decorator/SelectedDecorator.h"

namespace App
{

    TriangleFigure::TriangleFigure(Euclid::Triangle<Kernel>* triangle)
    {
        _triangle = triangle;
    }

    Euclid::Triangle<Kernel>*
    TriangleFigure::triangle()
    {
        return _triangle;
    }

    void
    TriangleFigure::paintGL() const
    {
        glBegin(GL_TRIANGLES);
        for (int i=0; i<3; i++)
        {
            const Euclid::Vertex<Kernel>* v = _triangle->vertex(i);
            glVertex3fv(v->point().toArray());
        }
        glEnd();
    }

    void
    TriangleFigure::clicked()
    {
        _triangle->setSelected(! _triangle->isSelected());
    }

    Viewer::FigureDecorator*
    TriangleFigure::decorations() const
    {
        Viewer::ComplexDecorator *decorator = new Viewer::ComplexDecorator;
        if (_triangle->isSelected()) {
            decorator->add(new SelectedDecorator(this));
        }
        if (MainWindow::viewNeighbors) {
            for (int i=0; i<3; i++)
            {
                const Euclid::Triangle<Kernel>* t = _triangle->neighbor(i);
                if (0 != t && t->isSelected()) {
                    decorator->add(new NeighborDecorator(this));
                }
            }
        }
        if (MainWindow::viewLepp
            && _triangle->info()) {
            decorator->add(new LeppDecorator(this));
        }
        decorator->add(new NormalDecorator(this));
        return decorator;
    }
}

