#pragma once

#include "Criterion.h"

namespace Euclid
{

    /*!
     * Longest edge criteria.
     */
    template <class Kernel>
    class LongestEdgeCriterion : public Criterion
    {
    public:
        LongestEdgeCriterion(T maxLength = 1.0)
            : Criterion()
        {
            _maxLength = maxLength;
        }

        bool test(Triangle<Kernel>* triangle)
        {
            for (int i=0; i<3; i++)
            {
                const Vector v = triangle->edge(i);
                if (_maxLength > 0) {
                    if (v.distance() > _maxLength) {
                        return true;
                    }
                } else {
                    if (v.distance() < -1.0*_maxLength) {
                        return true;
                    }
                }
            }

            return false;
        }

    private:
        T _maxLength;
    };
}

