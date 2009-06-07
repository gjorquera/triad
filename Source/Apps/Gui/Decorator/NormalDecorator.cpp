#include "NormalDecorator.h"
#include "../TriangleFigure.h"

namespace App
{

    NormalDecorator::NormalDecorator(const TriangleFigure* figure)
        : Viewer::FigureDecorator(figure)
    {
    }

    void
    NormalDecorator::paintGL() const
    {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        glColor3f(1.0, 1.0, 1.0);
        figure()->paintGL();

        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        glColor3f(0.0, 0.0, 0.0);
        figure()->paintGL();
    }
}

