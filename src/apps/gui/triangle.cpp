#include "triangle.h"
#include "decoratedtriangle.h"

namespace App
{

    Triangle::Triangle()
    {
    }

    void
    Triangle::render() const
    {
        glBegin(GL_LINE_LOOP);
            glVertex3f(0.0, 100.0, 0.0);
            glVertex3f(100.0, 0.0, 0.0);
            glVertex3f(100.0, 100.0, 0.0);
        glEnd();
    }

    Viewer::IFigure*
    Triangle::decorate() const
    {
        return new DecoratedTriangle(this);
    }
}

