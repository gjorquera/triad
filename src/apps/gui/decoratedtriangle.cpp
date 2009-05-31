#include "decoratedtriangle.h"
#include "triangle.h"

namespace App
{

    DecoratedTriangle::DecoratedTriangle(const Triangle* figure)
        : Viewer::DecoratedFigure(figure)
    {
    }

    void
    DecoratedTriangle::render() const
    {
        /// @todo OpenGL options depending on the triangle state.
        glColor3f(1.0, 0.0, 0.0);
        Viewer::DecoratedFigure::render();
    }
}

