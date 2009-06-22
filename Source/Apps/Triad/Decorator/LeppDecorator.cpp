#include "LeppDecorator.h"
#include "../TriangleFigure.h"

namespace App
{

    LeppDecorator::LeppDecorator(const TriangleFigure* figure)
        : Viewer::FigureDecorator(figure)
    {
    }

    void
    LeppDecorator::paintGL() const
    {
        glColor3f(0.8, 0.8, 0.8);
        glPushMatrix();
        glTranslatef(0.0, 0.0, -3.0);
        figure()->paintGL();
        glPopMatrix();
    }
}

