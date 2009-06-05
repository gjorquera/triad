#include <Viewer/ComplexDecorator.h>
#include "TriangleDecorator.h"
#include "../Decorator/SelectedDecorator.h"
#include "../Decorator/NeighborDecorator.h"

namespace App
{

    TriangleDecorator::TriangleDecorator(Euclid::Triangle<Kernel>* triangle)
    {
        _triangle = triangle;
    }

    Viewer::IFigure*
    TriangleDecorator::decorate() const
    {
        Viewer::ComplexDecorator *decorator = new Viewer::ComplexDecorator;
        decorator->add(new SelectedDecorator(this));
        decorator->add(new NeighborDecorator(this));
        return decorator;
    }
}

