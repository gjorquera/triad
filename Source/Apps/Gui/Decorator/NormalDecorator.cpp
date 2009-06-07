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
        glColor3f(1.0, 1.0, 1.0);
        glBegin(GL_TRIANGLES);
        figure()->paintGL();
        glEnd();

        glColor3f(0.0, 0.0, 0.0);
        glBegin(GL_LINE_LOOP);
        figure()->paintGL();
        glEnd();
    }
}

