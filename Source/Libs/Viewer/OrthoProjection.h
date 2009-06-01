#pragma once

#include "Projection.h"

namespace Viewer
{
    /*!
     * The OrthographicProjection class implements the orthographic projection
     * transformation.
     *
     * An orthographic projection can be specified either by it's \b znear and
     * \b zfar values or by it's \b width, \b height, \b znear and \b zfar
     * values.
     *
     * The first option defines a projection with dynamic resize policy. The
     * second option defines a projection with fixed resize policy. See
     * Projection for more information on the resize policy.
     *
     * The orthographic projection defines the projection volume as a cuboid
     * where the visualization window is a rectangle with coordinates (0, 0,
     * with, height) and the z clipping planes are located at znear and zfar.
     *
     * As the observer is looking at the negative values of the z axis, the \b
     * znear and \b zfar values are negative values, this means that an
     * orthographic projection with \b znear = 0 and \b zfar = 10 will draw
     * objects whose \c z coordinate are located in the range [0, -10[.
     */
    class OrthoProjection : public Projection
    {
    public:
        OrthoProjection(float znear, float zfar);
        OrthoProjection(float znear, float zfar, int width, int height);

    protected:
        float _znear;
        float _zfar;

        OrthoProjection();
        void apply() const;
    };
}

