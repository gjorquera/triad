#pragma once

#include <Euclid/Algorithm/LeppStrategy.h>
#include <Euclid/Algorithm/Lepp/Library.h>
#include "../Kernel.h"

namespace App
{

    /*!
     * Customization of the Euclid::LeppStrategy implementation.
     */
    class LeppStrategy : public Euclid::LeppStrategy<Kernel>
    {
    public:
        typedef Euclid::LeppLibrary<Kernel> LeppLibrary;

        LeppStrategy(Euclid::TriMesh<Kernel>* trimesh = 0);
        ~LeppStrategy();
        void highlightLepp();
        int averageLepp();
    };
}

