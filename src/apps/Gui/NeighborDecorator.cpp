#include "NeighborDecorator.h"
#include "Triangle.h"

namespace App
{

    NeighborDecorator::NeighborDecorator(const Triangle* figure)
        : Viewer::FigureDecorator(figure)
    {
    }

    void
    NeighborDecorator::render() const
    {
        glColor3f(0.5, 0.5, 0.5);
        glBegin(GL_TRIANGLES);
            glVertex3f(0.0, 100.0, -1.0);
            glVertex3f(100.0, 0.0, -1.0);
            glVertex3f(100.0, 100.0, -1.0);
        glEnd();
    }
}

