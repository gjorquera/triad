#pragma once

#include "../Geometry/Triangle.h"

namespace Euclid
{

    /*!
     * Algorithm triangle criteria base class.
     */
    template <class Kernel>
    class Criterion
    {
    public:
        typedef typename Kernel::T      T;
        typedef typename Kernel::Point  Point;
        typedef typename Kernel::Vector Vector;

        Criterion()
        {
        }

        virtual ~Criterion()
        {
        }

        virtual bool test(Triangle<Kernel>* triangle) const = 0;
    };
}

