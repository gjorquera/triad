#include "NeighborDecorator.h"
#include "../TriangleFigure.h"

namespace App
{

    NeighborDecorator::NeighborDecorator(const TriangleFigure* figure)
        : Viewer::FigureDecorator(figure)
    {
    }

    void
    NeighborDecorator::paintGL() const
    {
        glColor3f(0.5, 0.5, 0.5);
        glBegin(GL_TRIANGLES);
            glVertex3f(0.0, 1.0, -1.0);
            glVertex3f(1.0, 0.0, -1.0);
            glVertex3f(1.0, 1.0, -1.0);
        glEnd();
    }
}

