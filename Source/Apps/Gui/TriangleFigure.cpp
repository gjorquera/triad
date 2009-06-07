#include <Viewer/ComplexDecorator.h>
#include "TriangleFigure.h"
#include "Decorator/NeighborDecorator.h"
#include "Decorator/NormalDecorator.h"
#include "Decorator/SelectedDecorator.h"

namespace App
{

    TriangleFigure::TriangleFigure(const Euclid::Triangle<Kernel>* triangle)
    {
        _triangle = triangle;
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

    Viewer::FigureDecorator*
    TriangleFigure::decorations() const
    {
        return new NormalDecorator(this);
        Viewer::ComplexDecorator *decorator = new Viewer::ComplexDecorator;
        decorator->add(new SelectedDecorator(this));
        decorator->add(new NeighborDecorator(this));
        return decorator;
    }
}

