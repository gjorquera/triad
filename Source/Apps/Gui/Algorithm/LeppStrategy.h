#pragma once

#include <Euclid/Algorithm/LeppStrategy.h>
#include "../Kernel.h"

namespace App
{

    /*!
     * Customization of the Euclid::LeppStrategy implementation.
     */
    class LeppStrategy : public Euclid::LeppStrategy<Kernel>
    {
    public:
        LeppStrategy(Euclid::TriMesh<Kernel>* trimesh = 0);
        ~LeppStrategy();
        void highlightLepp();
        int averageLepp();
    };
}

