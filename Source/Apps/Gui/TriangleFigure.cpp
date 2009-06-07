#include <Viewer/ComplexDecorator.h>
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
        _triangle->info().selected = (! _triangle->info().selected);
    }

    Viewer::FigureDecorator*
    TriangleFigure::decorations() const
    {
        Viewer::ComplexDecorator *decorator = new Viewer::ComplexDecorator;
        if (_triangle->info().selected) {
            decorator->add(new SelectedDecorator(this));
        }
        for (int i=0; i<3; i++)
        {
            const Euclid::Triangle<Kernel>* t = _triangle->neighbor(i);
            if (0 != t && t->info().selected) {
                decorator->add(new NeighborDecorator(this));
            }
        }
        //decorator->add(new LeppDecorator(this));
        decorator->add(new NormalDecorator(this));
        return decorator;
    }
}

