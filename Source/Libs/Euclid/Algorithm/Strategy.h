#pragma once

#include <cassert>
#include "Criterion.h"
#include "../Geometry/TriMesh.h"

namespace Euclid
{

    /*!
     * Represents refinement algorithms applyable to trimeshes.
     */
    template <class Kernel>
    class Strategy
    {
    public:
        Strategy(TriMesh<Kernel>* trimesh = 0)
        {
            _trimesh = trimesh;
        }

        virtual ~Strategy()
        {
        }

        void setTriMesh(TriMesh<Kernel>* trimesh)
        {
            assert(0 != trimesh);
            _trimesh = trimesh;
        }

        virtual void refine(Criterion<Kernel>& criterion) = 0;

    protected:
        TriMesh<Kernel>* trimesh()
        {
            assert(0 != _trimesh);
            return _trimesh;
        }

    private:
        TriMesh<Kernel>* _trimesh;
    };
}

