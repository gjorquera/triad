#pragma once

#include "Criterion.h"

namespace Euclid
{

    /*!
     * Selected criterion.
     *
     * The \b test method returns true if the given triangle is selected.
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

