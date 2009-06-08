#pragma once

#include <Euclid/Algorithm/Criterion.h>
#include "../Kernel.h"

namespace App
{

    /*!
     * Selected triangles criterion.
     */
    class SelectedCriterion : public Euclid::Criterion<Kernel>
    {
    public:
        SelectedCriterion();
        bool test(Euclid::Triangle<Kernel>* triangle) const;
    };
}

