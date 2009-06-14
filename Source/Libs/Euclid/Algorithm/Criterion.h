#pragma once

#include "../Geometry/Triangle.h"

namespace Euclid
{

    /*!
     * Algorithm triangle criteria base class.
     *
     * This class is used to select triangles for refinement (refining the
     * triangle only one time) or to refine until the triangle does not meet the
     * given criterion (refining the triangle as many times as necessary).
     *
     * Concrete criterion must implement the \b test method.
     */
    template <class Kernel>
    class Criterion
    {
    public:
        Criterion()
        {
        }

        virtual ~Criterion()
        {
        }

        virtual bool test(Triangle<Kernel>* triangle) const = 0;
    };
}

