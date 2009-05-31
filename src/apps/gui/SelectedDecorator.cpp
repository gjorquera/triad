#include "SelectedDecorator.h"
#include "Triangle.h"

namespace App
{

    SelectedDecorator::SelectedDecorator(const Triangle* figure)
        : Viewer::FigureDecorator(figure)
    {
    }

    void
    SelectedDecorator::render() const
    {
        /// @todo OpenGL options depending on the triangle state.
        glColor3f(1.0, 0.0, 0.0);
        glBegin(GL_LINE_LOOP);
            glVertex3f(0.0, 100.0, 0.0);
            glVertex3f(100.0, 0.0, 0.0);
            glVertex3f(100.0, 100.0, 0.0);
        glEnd();
    }
}

