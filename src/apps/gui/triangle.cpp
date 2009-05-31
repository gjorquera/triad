#include "triangle.h"
#include "decoratedtriangle.h"

namespace App
{

    Triangle::Triangle()
    {
    }

    Viewer::IFigure*
    Triangle::decorate() const
    {
        return new DecoratedTriangle(this);
    }
}

