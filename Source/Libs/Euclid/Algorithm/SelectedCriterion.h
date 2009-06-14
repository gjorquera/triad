#pragma once

#include "Criterion.h"

namespace Euclid
{

    /*!
     * Selected criterion.
     */
    template <class Kernel>
    class SelectedCriterion : public Criterion<Kernel>
    {
    public:
        typedef Triangle<Kernel> TriangleT;

        SelectedCriterion()
            : Criterion<Kernel>()
        {
        }

        bool test(TriangleT* triangle) const
        {
            bool selected = triangle->isSelected();
            triangle->setSelected(false);
            return selected;
        }
    };
}

