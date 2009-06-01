#pragma once

namespace Euclid
{

    /*!
     * The DefaultKernel structure defines the default type templates that the
     * geometry objects will use.
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

