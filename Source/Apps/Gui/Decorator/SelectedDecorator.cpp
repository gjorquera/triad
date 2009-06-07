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
        glColor3f(1.0, 0.0, 0.0);
        glPushMatrix();
        glTranslatef(0.0, 0.0, 4.0);
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        figure()->paintGL();
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        glPopMatrix();
    }
}

