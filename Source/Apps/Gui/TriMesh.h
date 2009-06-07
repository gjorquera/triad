#pragma once

#include <Euclid/Algorithm/Criterion.h>
#include <Euclid/Geometry/TriMesh.h>
#include "Kernel.h"

namespace App
{

    class TriMesh : public Euclid::TriMesh<Kernel>
    {
    public:
        TriMesh();
        void select(const Euclid::Criterion<Kernel>& criterion);
    };
}

