#include "OrthographicProjection.h"

namespace Viewer
{

    OrthographicProjection::OrthographicProjection()
    {
    }

    OrthographicProjection::OrthographicProjection(float znear, float zfar)
        : Projection(0.0, 0.0, DYNAMIC)
    {
        _znear = znear;
        _zfar = zfar;
    }

    OrthographicProjection::OrthographicProjection(float width, float height,
        float znear, float zfar)
        : Projection(width, height, FIXED)
    {
        _znear = znear;
        _zfar = zfar;
    }

    void
    OrthographicProjection::apply() const
    {
        glOrtho(0, _width, 0, _height, _znear, _zfar);
    }
}

