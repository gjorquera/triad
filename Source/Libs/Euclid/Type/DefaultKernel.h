#pragma once

#include "Point.h"
#include "Vector.h"

namespace Euclid
{

    /*!
     * The DefaultKernel structure defines the default type templates that the
     * geometry objects will use.
     *
     * Using this structure as a template argument for a class enables that
     * class to work with different type of Point and Vector parametrizations.
     */
    struct DefaultKernel
    {
        typedef float T;
        typedef Point<3,T> Point;
        typedef Vector<3,T> Vector;
        typedef int VertexInfo;
        typedef int TriangleInfo;
    };
}

