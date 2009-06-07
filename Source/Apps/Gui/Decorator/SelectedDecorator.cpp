#include "SelectedDecorator.h"
#include "../TriangleFigure.h"

namespace App
{

    SelectedDecorator::SelectedDecorator(const TriangleFigure* figure)
        : Viewer::FigureDecorator(figure)
    {
    }

    void
    SelectedDecorator::paintGL() const
    {
        glColor3f(1.0, 0.6, 0.4);
        glPushMatrix();
        glTranslatef(0.0, 0.0, -2.0);
        figure()->paintGL();
        glPopMatrix();
    }
}

