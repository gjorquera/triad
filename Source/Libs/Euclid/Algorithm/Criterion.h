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
        Criterion()
        {
        }

        virtual ~Criterion()
        {
        }

        virtual bool test(Triangle<Kernel>* triangle) const = 0;
    };
}

