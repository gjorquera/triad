#pragma once

#include <Euclid/Algorithm/LeppStrategy.h>
#include "../Kernel.h"

namespace App
{

    /*!
     * Naive lepp bisection customization.
     */
    class LeppStrategy : public Euclid::LeppStrategy<Kernel>
    {
    public:
        LeppStrategy(Euclid::TriMesh<Kernel>* trimesh);
        ~LeppStrategy();
        void highlightLepp();
    };
}

