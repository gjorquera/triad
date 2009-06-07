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
        /// @todo OpenGL options depending on the triangle state.
        glColor3f(1.0, 0.0, 0.0);
        glBegin(GL_LINE_LOOP);
            glVertex3f(0.0, 1.0, 0.0);
            glVertex3f(1.0, 0.0, 0.0);
            glVertex3f(1.0, 1.0, 0.0);
        glEnd();
    }
}

