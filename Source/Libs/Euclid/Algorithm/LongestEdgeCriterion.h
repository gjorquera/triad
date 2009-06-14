#pragma once

#include "Criterion.h"

namespace Euclid
{

    /*!
     * Longest edge criterion.
     *
     * The \b test method returns true depending on the size of the longest edge
     * of the given triangle.
     */
    template <class Kernel>
    class LongestEdgeCriterion : public Criterion<Kernel>
    {
    public:
        typedef typename Kernel::T      T;
        typedef typename Kernel::Vector Vector;
        typedef Triangle<Kernel>        TriangleT;

        LongestEdgeCriterion(T maxLength = 1.0, bool biggest = true)
            : Criterion<Kernel>()
        {
            _maxLength = maxLength;
            _biggest = biggest;
        }

        bool test(TriangleT* triangle) const
        {
            bool result = false;
            for (int i=0; i<3; i++)
            {
                const Vector v = triangle->edge(i)->vector();
                if (_biggest && v.distance() > _maxLength
                    || ! _biggest && v.distance() < _maxLength) {
                    result = true;
                }
            }

            return result;
        }

    private:
        T _maxLength;
        bool _biggest;
    };
}

