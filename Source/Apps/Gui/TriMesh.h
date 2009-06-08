#pragma once

#include <Euclid/Algorithm/Criterion.h>
#include <Euclid/Geometry/TriMesh.h>
#include "Kernel.h"

namespace App
{

    /*!
     * Customization of the TriMesh class.
     */
    class TriMesh : public Euclid::TriMesh<Kernel>
    {
    public:
        TriMesh();
        void select(const Euclid::Criterion<Kernel>& criterion);
    };
}

