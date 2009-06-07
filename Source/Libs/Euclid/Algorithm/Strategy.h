#pragma once

#include <cassert>
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

        virtual void refine(Criterion& criterion) = 0;

    protected:
        TriMesh<Kernel>* trimesh()
        {
            return _trimesh;
        }

    private:
        TriMesh<Kernel>* _trimesh;
    };
}

