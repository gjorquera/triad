#include <Viewer/ComplexDecorator.h>
#include "Triangle.h"
#include "Decorator/SelectedDecorator.h"
#include "Decorator/NeighborDecorator.h"

namespace App
{

    Triangle::Triangle()
    {
    }

    Viewer::IFigure*
    Triangle::decorate() const
    {
        Viewer::ComplexDecorator *decorator = new Viewer::ComplexDecorator;
        decorator->add(new SelectedDecorator(this));
        decorator->add(new NeighborDecorator(this));
        return decorator;
    }
}

