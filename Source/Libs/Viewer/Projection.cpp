#include "Projection.h"

namespace Viewer
{

    Projection::Projection()
    {
    }

    Projection::Projection(float width, float height,
        RedimensionPolicy redimensionPolicy)
    {
        _width = width;
        _height = height;
        _redimensionPolicy = redimensionPolicy;
    }

    /*virtual*/
    Projection::~Projection()
    {
    }

    void
    Projection::resize(int width, int height)
    {
        if (_redimensionPolicy == DYNAMIC) {
            _width = width;
            _height = height;
        }
    }
}

