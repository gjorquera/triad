#include "decoratedtriangle.h"

namespace App
{

    DecoratedTriangle::DecoratedTriangle(Viewer::IFigure *figure)
        : Viewer::DecoratedFigure(figure)
    {
    }

    void
    DecoratedTriangle::render()
    {
        /// @todo OpenGL options depending on the triangle state.
        glColor3f(1.0, 0.0, 0.0);
        DecoratedFigure::render();
    }
}

