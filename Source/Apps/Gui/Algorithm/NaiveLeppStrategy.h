#pragma once

#include <Euclid/Algorithm/NaiveLeppStrategy.h>
#include "../Kernel.h"

namespace App
{

    /*!
     * Naive lepp bisection customization.
     */
    class NaiveLeppStrategy : public Euclid::NaiveLeppStrategy<Kernel>
    {
    public:
        NaiveLeppStrategy(Euclid::TriMesh<Kernel>* trimesh);
        ~NaiveLeppStrategy();
        void highlightLepp();
    };
}

