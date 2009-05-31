#include "triangle.h"
#include "decoratedtriangle.h"

namespace App
{

    Triangle::Triangle()
    {
    }

    void
    Triangle::render()
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
        Triangle* triangle = const_cast<Triangle*>(this);
        return new DecoratedTriangle(triangle);
    }
}

