#pragma once

#include <cassert>
#include "Criterion.h"
#include "../Geometry/TriMesh.h"

namespace Euclid
{

    template <class Kernel>
    class Strategy
    {
    public:
        Strategy(TriMesh<Kernel>* trimesh)
        {
            assert(0 != trimesh);
            _trimesh = trimesh;
        }

        virtual ~Strategy()
        {
        }

        virtual void refine(Criterion<Kernel>& criterion) = 0;

    protected:
        TriMesh<Kernel>* trimesh()
        {
            return _trimesh;
        }

    private:
        TriMesh<Kernel>* _trimesh;
    };
}

