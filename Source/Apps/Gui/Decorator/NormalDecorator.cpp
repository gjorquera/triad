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
        glPushMatrix();
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        glColor3f(1.0, 1.0, 1.0);
        glTranslatef(0.0, 0.0, -4.0);
        figure()->paintGL();
        glPopMatrix();

        glPushMatrix();
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        glTranslatef(0.0, 0.0, -2.0);
        glColor3f(0.0, 0.0, 0.0);
        figure()->paintGL();
        glPopMatrix();
    }
}

