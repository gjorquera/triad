#pragma once

#include "Criterion.h"

namespace Euclid
{

    /*!
     * Longest edge criteria.
     */
    template <class Kernel>
    class LongestEdgeCriterion : public Criterion<Kernel>
    {
    public:
        typedef typename Kernel::T      T;
        typedef typename Kernel::Vector Vector;

        LongestEdgeCriterion(T maxLength = 1.0, bool biggest = true)
            : Criterion<Kernel>()
        {
            _maxLength = maxLength;
            _biggest = biggest;
        }

        bool test(Triangle<Kernel>* triangle) const
        {
            bool result = false;
            for (int i=0; i<3; i++)
            {
                const Vector* v = triangle->edge(i);
                if (_biggest && v->distance() > _maxLength
                    || ! _biggest && v->distance() < _maxLength) {
                    result = true;
                }
                delete v;
            }

            return result;
        }

    private:
        T _maxLength;
        bool _biggest;
    };
}
