#include <Viewer/ComplexDecorator.h>
#include "Triangle.h"
#include "decoratedtriangle.h"
#include "neighbordecorator.h"

namespace App
{

    Triangle::Triangle()
    {
    }

    Viewer::IFigure*
    Triangle::decorate() const
    {
        Viewer::ComplexDecorator *decorator = new Viewer::ComplexDecorator;
        decorator->add(new DecoratedTriangle(this));
        decorator->add(new NeighborDecorator(this));
        return decorator;
    }
}

