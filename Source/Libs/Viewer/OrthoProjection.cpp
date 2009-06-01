#include "OrthoProjection.h"

namespace Viewer
{

    OrthoProjection::OrthoProjection()
    {
    }

    OrthoProjection::OrthoProjection(float znear, float zfar)
        : Projection(0, 0, DYNAMIC)
    {
        _znear = znear;
        _zfar = zfar;
    }

    OrthoProjection::OrthoProjection(float znear, float zfar, int width,
        int height)
        : Projection(width, height, FIXED)
    {
        _znear = znear;
        _zfar = zfar;
    }

    void
    OrthoProjection::apply() const
    {
        glOrtho(0, _width, 0, _height, _znear, _zfar);
    }
}

