#include <Viewer/ComplexDecoration.h>
#include "triangle.h"
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
        Viewer::ComplexDecoration *decorator = new Viewer::ComplexDecoration;
        decorator->add(new DecoratedTriangle(this));
        decorator->add(new NeighborDecorator(this));
        return decorator;
    }
}

