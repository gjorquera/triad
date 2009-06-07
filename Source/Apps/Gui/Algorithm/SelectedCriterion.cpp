#include "SelectedCriterion.h"

namespace App
{

    SelectedCriterion::SelectedCriterion()
        : Euclid::Criterion<Kernel>()
    {
    }

    bool
    SelectedCriterion::test(Euclid::Triangle<Kernel>* triangle) const
    {
        return triangle->info().selected;
    }
}

