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
        glColor3f(0.0, 1.0, 0.0);
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        glLineWidth(2.0);
        figure()->paintGL();
        glLineWidth(1.0);
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }
}

